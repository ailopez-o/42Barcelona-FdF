
import Cocoa
import Metal
import MetalKit
import Darwin

import mlx_image


class WinEvent: NSWindow
{
  var eventFuncts = [UnsafeMutableRawPointer?]()
  var eventParams = [UnsafeMutableRawPointer]()

  var keyrepeat = 1
  var keyflag:UInt32 = 0

  var size_y:Int

  init(frame rect:CGRect)
  {
    for _ in 0...31
    {
      eventFuncts.append(Optional.none)
      eventParams.append(UnsafeMutableRawPointer(&keyrepeat)) /// dummy address here, null not needed
    }

    let wsm = NSWindow.StyleMask(rawValue: NSWindow.StyleMask.titled.rawValue|NSWindow.StyleMask.closable.rawValue|NSWindow.StyleMask.miniaturizable.rawValue)
    let bck = NSWindow.BackingStoreType.buffered
    size_y = Int(rect.size.height)
    super.init(contentRect: rect, styleMask: wsm, backing: bck, defer: false)
  }

  func setNotifs()
  {
      NotificationCenter.default.addObserver(self, selector: #selector(exposeNotification(_:)), name: NSWindow.didBecomeKeyNotification, object: nil)
      NotificationCenter.default.addObserver(self, selector: #selector(deminiaturizeNotification(_:)), name: NSWindow.didDeminiaturizeNotification, object: nil)
      NotificationCenter.default.addObserver(self, selector: #selector(closeNotification(_:)), name: NSWindow.willCloseNotification, object: nil)

/***
      [[NSNotificationCenter defaultCenter] addObserver:win selector:@selector(exposeNotification:) name:@"NSWindowDidBecomeKeyNotification" object:win];
      [[NSNotificationCenter defaultCenter] addObserver:win selector:@selector(deminiaturizeNotification:) name:@"NSWindowDidDeminiaturizeNotification" object:win];
      [[NSNotificationCenter defaultCenter] addObserver:win selector:@selector(closeNotification:) name:@"NSWindowWillCloseNotification" object:win];
***/

  }

  public func setKeyRepeat(_ mode:Int)
  {
	keyrepeat = mode;
  }


  func addHook(index idx:Int, fct fptr:UnsafeMutableRawPointer?, param pptr:UnsafeMutableRawPointer)
  {
	eventFuncts[idx] = fptr;
	eventParams[idx] = pptr;
	if (idx == 6 || idx == 32)
	{
		if (fptr != nil) ///  == nullptr)
		   { self.acceptsMouseMovedEvents = false }
		else { self.acceptsMouseMovedEvents = true }
	}
  }


  override func keyDown(with event: NSEvent)
  {
	/// print("got keydown with code: \(event.keyCode) ")
	if (event.isARepeat && keyrepeat == 0)
	 { return }
	if (eventFuncts[2] != nil)
	{
	  _ = unsafeBitCast(eventFuncts[2],to:(@convention(c)(Int32, UnsafeRawPointer)->Int32).self)(Int32(event.keyCode), eventParams[2])
	}
  }


  override func keyUp(with event: NSEvent)
  {
	/// print("got keyup with code: \(event.keyCode) and calling key hook")
	if (event.isARepeat && keyrepeat == 0)
	 { return }
	if (eventFuncts[3] != nil)
	{
	  _ = unsafeBitCast(eventFuncts[3],to:(@convention(c)(Int32, UnsafeRawPointer)->Int32).self)(Int32(event.keyCode), eventParams[3])
	}
  }


  func get_mouse_button(with ev:NSEvent) -> Int
  {
	switch (ev.type) {
  	       case NSEvent.EventType.leftMouseDown,
	       	    NSEvent.EventType.leftMouseUp,
	       	    NSEvent.EventType.leftMouseDragged:
	           return 1;
	       case NSEvent.EventType.rightMouseDown,
	       	    NSEvent.EventType.rightMouseUp,
	            NSEvent.EventType.rightMouseDragged:
	           return 2;
	       case NSEvent.EventType.otherMouseDown,
	            NSEvent.EventType.otherMouseUp,
	            NSEvent.EventType.otherMouseDragged:
	           return 3;
	       default:
	           return 0;
        }
  }



  func mouse(with event: NSEvent, index idx:Int, type t:Int)
  {
	var thepoint:NSPoint
	var button:Int

	thepoint = event.locationInWindow
	button = get_mouse_button(with:event)
	/// button = event.buttonNumber
	/// print(" mouse down button \(event.buttonNumber) at location \(thepoint.x) x \(thepoint.y)")
	if (eventFuncts[idx] != nil)
	{
	  if (t == 0)
	   { _ = unsafeBitCast(eventFuncts[idx],to:(@convention(c)(Int32, Int32, Int32, UnsafeRawPointer)->Int32).self)(Int32(button), Int32(thepoint.x), Int32(size_y-1-Int(thepoint.y)), eventParams[idx]) }
	  if (t == 1)
	   { _ = unsafeBitCast(eventFuncts[idx],to:(@convention(c)(Int32, Int32, UnsafeRawPointer)->Int32).self)(Int32(thepoint.x), Int32(size_y-1-Int(thepoint.y)), eventParams[idx]) }
	}
  }

  override func mouseDown(with event: NSEvent)  { mouse(with:event, index:4, type:0)  }
  override func rightMouseDown(with event: NSEvent)   {	mouse(with:event, index:4, type:0)  }
  override func otherMouseDown(with event: NSEvent)   {	mouse(with:event, index:4, type:0)  }

  override func mouseUp(with event: NSEvent)  { mouse(with:event, index:5, type:0)  }
  override func rightMouseUp(with event: NSEvent)   { mouse(with:event, index:5, type:0)  }
  override func otherMouseUp(with event: NSEvent)   { mouse(with:event, index:5, type:0)  }

  override func mouseMoved(with event: NSEvent)   { mouse(with:event, index:6, type:1)  }
  override func mouseDragged(with event: NSEvent)   { mouse(with:event, index:6, type:1)  }
  override func rightMouseDragged(with event: NSEvent)   { mouse(with:event, index:6, type:1)  }
  override func otherMouseDragged(with event: NSEvent)   { mouse(with:event, index:6, type:1)  }


  override func scrollWheel(with event: NSEvent)
  {
	var thepoint:NSPoint
	var button = 0;

	thepoint = event.locationInWindow
	if (event.deltaY > 0.2) { button = 4; }
	if (event.deltaY < -0.2) { button = 5; }
	if (event.deltaX > 0.2) { button = 6; }
	if (event.deltaX < -0.2) { button = 7; }
        if (button != 0 && eventFuncts[4] != nil)
        {
          _ = unsafeBitCast(eventFuncts[4],to:(@convention(c)(Int32, Int32, Int32, UnsafeRawPointer)->Int32).self)(Int32(button), Int32(thepoint.x), Int32(thepoint.y), eventParams[4])
        }
  } 


  override func flagsChanged(with event: NSEvent)
  {
	var flag:UInt32
	var the_key:Int32
	var val:UInt32

	flag = UInt32(event.modifierFlags.rawValue)
	val = (keyflag|flag)&(~(keyflag&flag))
	if (val == 0)
	    { return }   /// no change - can happen when loosing focus on special key pressed, then re-pressed later
         the_key = 1
	 while (((val >> (the_key-1)) & 0x01)==0)
	  { the_key += 1 }
	 if (flag > keyflag && eventFuncts[2] != nil)
	   { _ = unsafeBitCast(eventFuncts[2],to:(@convention(c)(Int32, UnsafeRawPointer)->Int32).self)(0xFF+the_key, eventParams[2]) }
	 if (flag < keyflag && eventFuncts[3] != nil)
	   { _ = unsafeBitCast(eventFuncts[3],to:(@convention(c)(Int32, UnsafeRawPointer)->Int32).self)(0xFF+the_key, eventParams[3]) }
	 keyflag = flag
  }


  @objc func exposeNotification(_ notification:Notification)
  {
	if (eventFuncts[12] != nil)
	{
	  _ = unsafeBitCast(eventFuncts[12],to:(@convention(c)(UnsafeRawPointer)->Int32).self)(eventParams[12])
	}
  }

  @objc func closeNotification(_ notification:Notification)
  {
	if (eventFuncts[17] != nil)
	{
	  _ = unsafeBitCast(eventFuncts[17],to:(@convention(c)(UnsafeRawPointer)->Int32).self)(eventParams[17])
	}
  }

  @objc func deminiaturizeNotification(_ notification:Notification)
  {
	exposeNotification(notification)
  }



}


public class MlxWin
{
  var winE: WinEvent

  var device: MTLDevice
  var mview: MTKView
  var md: MTKVDelegate

  public init(device d:MTLDevice, width w:Int, height h:Int, title t:String)
  {
    let rect = CGRect(x: 100, y: 100, width: w, height: h)
    winE = WinEvent(frame: rect)

    device = d
    mview = MTKView(frame: rect, device:device)
    mview.clearColor = MTLClearColorMake(0, 0, 0, 0)
    mview.colorPixelFormat = .bgra8Unorm
    mview.isPaused = true
    mview.enableSetNeedsDisplay = false
    md = MTKVDelegate(view:mview, device:device)
    mview.delegate = md
    clearWin()

    winE.contentView = mview
    winE.title = t
    winE.makeKeyAndOrderFront(self)
  }

/// winEvent calls
  public func getWinEFrame() -> NSRect  { return winE.frame }
  public func getScreenFrame() -> NSRect { return winE.screen!.frame }
  public func getMouseLoc() -> NSPoint { return winE.mouseLocationOutsideOfEventStream }
  public func addHook(index idx:Int, fct fptr:UnsafeMutableRawPointer, param pptr:UnsafeMutableRawPointer)
  {  winE.addHook(index: idx, fct: fptr, param: pptr)  }
  public func setKeyRepeat(_ mode:Int)  { winE.setKeyRepeat(mode) }
  public func destroyWinE()  { winE.close() }
  public func setNotifs() { winE.setNotifs() }

/// mtkviewdelegate calls
  public func clearWin()  {  md.clearWin() }
  public func pixelPut(_ x:Int32, _ y:Int32, _ color:UInt32)  {  md.pixelPut(x, y, color) }
  public func putImageScale(image img:MlxImg, sx srcx:Int32, sy srcy:Int32, sw srcw:Int32, sh srch:Int32, dx posx:Int32, dy posy:Int32, dw dest_w:Int32, dh dest_h:Int32, c color:UInt32) { md.putImageScale(img, srcx, srcy, srcw, srch, posx, posy, dest_w, dest_h, color) }
///  	      			  	      	  print("putimagescale \(srcx) \(srcy) \(srcw) \(srch) \(posx) \(posy) \(dest_w) \(dest_h) \(color)") }
  public func putImage(image img:MlxImg, x posx:Int32, y posy:Int32) { md.putImage(img, posx, posy) }
  public func waitForGPU() { md.waitForGPU() }
  public func flushPixels() { md.flushPixels() }
  public func flushImages() { md.flushImages() }

}




let shaders = """
#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float4 position;
    float4 UV;
};
struct VertexOut {
    float4 position [[ position ]];
    float4 color;
    float2 UV;
};
struct uniforms {
   packed_float2 origin_size;
   packed_float2 origin_pos;
   packed_float2 origin_sub;
   packed_float2 dest_size;
   packed_float2 dest_pos;
   packed_float2 dest_sub;
   packed_float4 color;
};
vertex VertexOut basic_vertex_function(const device VertexIn *vertices [[ buffer(0) ]], constant uniforms& uni [[ buffer(1) ]],
uint vertexID [[ vertex_id ]])
{
    VertexOut vOut;
    float4 start = float4((2.0*uni.dest_pos.x)/(uni.dest_size.x-1.0) - 1.0, 1.0 - (2.0*uni.dest_pos.y)/(uni.dest_size.y-1.0) - (uni.dest_sub.y*2.0)/uni.dest_size.y, 0.0, 0.0);
 /*   vOut.position = (start + (vertices[vertexID].position + 1.0) * float4(uni.dest_sub, 0.0, 0.0))/float4(uni.dest_size, 1.0, 1.0); */

    vOut.position = float4(start.x+((vertices[vertexID].position.x + 1.0)*uni.dest_sub.x)/(uni.dest_size.x),
    		    	   start.y+((vertices[vertexID].position.y + 1.0)*uni.dest_sub.y)/(uni.dest_size.y), 0.0, 1.0);

    vOut.UV = (uni.origin_pos + float2(vertices[vertexID].UV.x, vertices[vertexID].UV.y)*(uni.origin_sub-1.0))/(uni.origin_size-1.0);
    vOut.color = uni.color;
    return vOut;
}
fragment float4 basic_fragment_function(VertexOut vIn [[ stage_in ]], texture2d<float> texture [[ texture(0) ]])
{
    constexpr sampler textureSampler(address::clamp_to_edge);
    return vIn.color*texture.sample(textureSampler, vIn.UV);
}
"""

struct textureList
{
   var uniformBuffer: MTLBuffer!
   var uniform_data:UnsafeMutablePointer<Float>
   var texture:MTLTexture
}


class MTKVDelegate: NSObject, MTKViewDelegate
{
  var device: MTLDevice
  var mview: MTKView
  var commandQueue: MTLCommandQueue!
  var pipelineState: MTLRenderPipelineState!
/// 3 params to pipeline
  var vertexBuffer: MTLBuffer!

///  var uniformBuffer: MTLBuffer!
///  var uniform_data:UnsafeMutablePointer<Float>
///  var texture: MTLTexture

  var texture_list: Array<textureList> = Array()
  var texture_list_count = 0

  var pixel_image:MlxImg
  var pixel_count:Int

  var drawable_texture: MTLTexture

  var doClear = false

  var GPUbatch = 0



   init(view: MTKView, device: MTLDevice)
   {
    self.mview = view
    self.device = device

    commandQueue = device.makeCommandQueue()!

    /// vertex buffer & shaders stay the always the same.

    let lib = try! device.makeLibrary(source: shaders, options: nil)
    let vertexFunction = lib.makeFunction(name: "basic_vertex_function")
    let fragmentFunction = lib.makeFunction(name: "basic_fragment_function")
    let pipelineDesc = MTLRenderPipelineDescriptor()
    pipelineDesc.colorAttachments[0].pixelFormat = .bgra8Unorm

    pipelineDesc.colorAttachments[0].isBlendingEnabled = true
    pipelineDesc.colorAttachments[0].rgbBlendOperation = .add
    pipelineDesc.colorAttachments[0].alphaBlendOperation = .add
    pipelineDesc.colorAttachments[0].sourceRGBBlendFactor = .oneMinusSourceAlpha
    pipelineDesc.colorAttachments[0].sourceAlphaBlendFactor = .oneMinusSourceAlpha
    pipelineDesc.colorAttachments[0].destinationRGBBlendFactor = .sourceAlpha
    pipelineDesc.colorAttachments[0].destinationAlphaBlendFactor = .sourceAlpha

    pipelineDesc.vertexFunction = vertexFunction
    pipelineDesc.fragmentFunction = fragmentFunction
    pipelineState = try! device.makeRenderPipelineState(descriptor: pipelineDesc)

    let vertexData: [Float] = [
       -1.0, -1.0, 0.0, 1.0,  0.0, 1.0, 0.0, 0.0,
       -1.0, 1.0, 0.0, 1.0,   0.0, 0.0, 0.0, 0.0,
       1.0, -1.0, 0.0, 1.0,   1.0, 1.0, 0.0, 0.0,
       1.0, -1.0, 0.0, 1.0,   1.0, 1.0, 0.0, 0.0,
       -1.0, 1.0, 0.0, 1.0,   0.0, 0.0, 0.0, 0.0,
       1.0, 1.0, 0.0, 1.0,    1.0, 0.0, 0.0, 0.0  ]
    var dataSize = vertexData.count * MemoryLayout.size(ofValue: vertexData[0])
    vertexBuffer = device.makeBuffer(bytes: vertexData, length: dataSize, options: []) 

    let vrect = view.frame

    drawable_texture = view.currentDrawable!.texture

    pixel_image = MlxImg(d: device, w:Int(vrect.size.width), h:Int(vrect.size.height))
    for i in 0...(pixel_image.texture_height*pixel_image.texture_sizeline/4-1)
      { pixel_image.texture_data[i] = UInt32(0xFF000000) }
    pixel_count = 0

    let uniformData: [Float] = [ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Float(vrect.size.width), Float(vrect.size.height), 0.0, 0.0, 0.0, 0.0,
    		     	       1.0, 1.0, 1.0, 1.0 ]
    dataSize = uniformData.count * MemoryLayout.size(ofValue: uniformData[0])
    for _ in 0...255
    { 
      let uniformBuffer = device.makeBuffer(bytes: uniformData, length: dataSize, options: [])!
      let uniform_data = (uniformBuffer.contents()).assumingMemoryBound(to:Float.self)
      texture_list.append(textureList(uniformBuffer:uniformBuffer, uniform_data:uniform_data, texture:pixel_image.texture)) }

    super.init()
   }


  func clearWin()
  {
	doClear = true
	mview.draw()
  }

  func pixelPut(_ x:Int32, _ y:Int32, _ color:UInt32)
  {
	pixel_image.texture_data[Int(y)*pixel_image.texture_sizeline/4+Int(x)] = color
	pixel_count += 1
	if (pixel_count >= 200000)
	{
		flushPixels()
	}
  }

  func flushPixels()
  {
	if (pixel_count > 0)
	{
	  
	  self.putImage(pixel_image, 0, 0)
	  self.flushImages()
	  for i in 0...pixel_image.texture_height*pixel_image.texture_sizeline/4-1
	    { pixel_image.texture_data[i] = UInt32(0xFF000000) }
	  pixel_count = 0
	}
  }

  func flushImages()
  {
	if (texture_list_count > 0)
	 {
	    mview.draw()
	  }
  }

  func putImage(_ img:MlxImg, _ x:Int32, _ y:Int32)
  {
	putImageScale(img, 0, 0, Int32(img.texture_width), Int32(img.texture_height), 
			   x, y, Int32(img.texture_width), Int32(img.texture_height),
			   UInt32(0xFFFFFFFF))
  }

  func putImageScale(_ img:MlxImg, _ src_x:Int32, _ src_y:Int32, _ src_w:Int32, _ src_h:Int32, _ dest_x:Int32, _ dest_y:Int32, _ dest_w:Int32, _ dest_h:Int32, _ color:UInt32)
  {
	if (texture_list_count == 0) /// means  I just draw
	{
		waitForGPU()    /// to be able to write again in uniforms
	}
	texture_list[texture_list_count].uniform_data[0] = Float(img.texture_width)
	texture_list[texture_list_count].uniform_data[1] = Float(img.texture_height)
	texture_list[texture_list_count].uniform_data[2] = Float(src_x)
	texture_list[texture_list_count].uniform_data[3] = Float(src_y)
	texture_list[texture_list_count].uniform_data[4] = Float(src_w)
	texture_list[texture_list_count].uniform_data[5] = Float(src_h)

	texture_list[texture_list_count].uniform_data[8] = Float(dest_x)
	texture_list[texture_list_count].uniform_data[9] = Float(dest_y)
	texture_list[texture_list_count].uniform_data[10] = Float(dest_w)
	texture_list[texture_list_count].uniform_data[11] = Float(dest_h)

	texture_list[texture_list_count].uniform_data[12] = Float((color>>16)&0xFF)/255.0;
	texture_list[texture_list_count].uniform_data[13] = Float((color>>8)&0xFF)/255.0;
	texture_list[texture_list_count].uniform_data[14] = Float((color>>0)&0xFF)/255.0;
	texture_list[texture_list_count].uniform_data[15] = Float((color>>24)&0xFF)/255.0;

	texture_list[texture_list_count].texture = img.texture
	texture_list_count += 1
	if (texture_list_count >= 256)
	{
		flushImages()
	}
  }

  public func waitForGPU()
  {
	while (GPUbatch > 0) { }
  }

  // 2 delegate MTKView functs

  func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize)
  {

  }

  func draw(in view: MTKView)
  {
	let commandBuffer = commandQueue.makeCommandBuffer()!
	if let renderPassDescriptor = view.currentRenderPassDescriptor
	 {
		renderPassDescriptor.colorAttachments[0].storeAction = .store
		if (doClear)
		{
		  renderPassDescriptor.colorAttachments[0].loadAction = .clear
                  renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColor(red: 0.0, green: 0.0, blue: 0.0, alpha:0.0)
		  let commandEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor)!
		  commandEncoder.endEncoding()
		  doClear = false
		}
		else
		{

/// first draw back prev buffer
		  let commandBEncoder = commandBuffer.makeBlitCommandEncoder()!
	 	  commandBEncoder.copy(from:drawable_texture, sourceSlice:0, sourceLevel:0, sourceOrigin: MTLOriginMake(0,0,0), sourceSize: MTLSizeMake(drawable_texture.width, drawable_texture.height, 1),  to:view.currentDrawable!.texture, destinationSlice:0, destinationLevel:0, destinationOrigin: MTLOriginMake(0,0,0))
	 	  commandBEncoder.endEncoding()


/// then draw the images
		  renderPassDescriptor.colorAttachments[0].loadAction = .load

		  var i = 0
		  while i < texture_list_count
		  {
		   let commandEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor)!
		   commandEncoder.setRenderPipelineState(pipelineState)
		   commandEncoder.setVertexBuffer(vertexBuffer, offset: 0, index: 0)
		   commandEncoder.setVertexBuffer(texture_list[i].uniformBuffer, offset: 0, index: 1)
		   commandEncoder.setFragmentTexture(texture_list[i].texture, index: 0)
		   commandEncoder.drawPrimitives(type: .triangleStrip, vertexStart: 0, vertexCount: 6, instanceCount:2)
		   commandEncoder.endEncoding()
		   i += 1
  		  }
		  texture_list_count = 0
                }	
         }
	commandBuffer.addCompletedHandler { cb in self.GPUbatch -= 1 }
	commandBuffer.present(view.currentDrawable!)
        commandBuffer.commit()
	GPUbatch += 1

	drawable_texture = view.currentDrawable!.texture
  }

}
