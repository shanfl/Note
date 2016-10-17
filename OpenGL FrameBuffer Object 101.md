##OpenGL FrameBuffer Object 101 
by Rob 'phantom' Jones
####Introduction

The Frame Buffer Object (FBO) extension was introduced to make Render to Texture objects much more efficient and much easier to perform when compared with the copying or pbuffer alternatives.

In this little article I’m going to give you a quick over view of how to use this extension and some things to keep in mind when using it so you can add faster Render to Texture functionality to your OpenGL programs.

####Setting Up

As with the other objects in OpenGL (texture object, pixel buffer objects and vertex buffer object) before you can use a FBO you have to create a valid handle to it:
```
GLuint fbo;
glGenFramebuffersEXT(1, &fbo);```
To perform any operations on a FBO you need to bind it, much like you would a VBO or texture, so that the operations can be performed on it, this is done via the following code
```
glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);```
The first parameter is the ‘target’ you wish to bind the framebuffer to, right now the only target you can use is the one indicated above however it is possible future extensions might allow you to bind it somewhere else. The fbo variable holds the handle to the FBO we requested earlier. To perform any FBO related operations you need to have a FBO bound or the calls will fail.


####Adding a Depth Buffer

A FBO on its own isn’t of much use, for it to be usable you have to attach some renderable objects to it; these can be textures or the newly introduced renderbuffers.

A renderbuffer are just objects which are used to support offscreen rendering, often for sections of the framebuffer which don’t have a texture format associated with them such as the stencil or depth buffer.

In this case we are going to use a renderbuffer to give our FBO a depth buffer to use while rendering.

Like the FBO we first of all have to get a handle to a valid **renderbuffer**:
```
GLuint depthbuffer;
glGenRenderbuffersEXT(1, &depthbuffer);```
Having successfully done this we need to bind the renderbuffer so that it is the current renderbuffer for the following operations:
```
glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthbuffer);```
As with a FBO bind the first parameter is the ‘target’ you wish to bind to, which right now can only be the indicated target. The depthbuffer variable holds the handle to the renderbuffer we’ll be working with after this.

At this point the renderbuffer doesn’t have any storage space associated with it, so we need to tell OpenGL how we want to use it and what size we’d like. In this case we are asking for a depth buffer of a certain size:
```
glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);```
Upon successful completion of the above code OpenGL will have allocated space for the renderbuffer to be used as a depth buffer with a given width and height. Note that renderbuffers can be used for normal RGB/RGBA storage and could be used to store stencil information.

Having reserved the space for the depth buffer the next job is to attach it to the FBO we created earlier.
```
glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);```
While it might look a bit imposing the function is pretty easy to understand; all it is doing is attaching the depthbuffer we created earlier to the currently bound FBO to its depth buffer attachment point.


####Adding a Texture To Render To

At this point we still don’t have a way of writing colour information to the FBO, so that is what we are going to add now. There are two ways of going about it:
- Attach a colour Renderbuffer to the FBO
- Attach a texture to the FBO

The former does have some uses; however it is the latter we will be covering here.

Before you can attach a texture you need to create one, this hasn’t changed from the normal way of using textures as you’ll see:
```
GLuint img;
glGenTextures(1, &img);
glBindTexture(GL_TEXTURE_2D, img);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);```

In this instance we are creating a normal RGBA image of **the same width and height** as the **renderbuffer** we created earlier; this is important as **ALL** attachments to a FBO have to be the same width and height. Note that we don’t upload any data, the space is just reserved by OpenGL so we can use it later.

Having created our texture the next job is to attach it to the FBO so we can render to it:
```
glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img, 0);```
Again this might look imposing but it isn’t that bad, the **GL_COLOR_ATTACHMENT0_EXT** tells OpenGL to attach it to the relevent attachment point (FBOs can have more than one colour buffer attached at any given time, each one to a different point), the **GL_TEXTURE_2D** tells OpenGL the format of the texture we are going to be attaching, img is the texture we’ll be attaching and the ‘0’ refers to the mipmap level of the texture you want to attach to, which you will generally want to leave as 0.

The final job to do in setup is to check that the FBO is ‘complete’. Completeness refers to the state of the FBO being one which, given the current OpenGL state and its attachments, all is correct for you to render to it.

This test is done via a single function which returns the status of the currently bound FBO
```
GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);```
If all has gone well then status will equal **GL_FRAMEBUFFER_COMPLETE_EXT** and your FBO is ready to be rendered to. Other error codes, as found in the spec, indicate other problems which might well have occurred when you tried to setup the FBO.


####Rendering to Texture

With all the hard work setting things up done the usage of the FBO from here on out is in fact pretty simple and relies on just one function call: glBindFramebufferEXT().

To render to a FBO you bind it and to stop rendering to it you call the above again with ‘0’ as the final parameter:
```
glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
glPushAttrib(GL_VIEWPORT_BIT);
glViewport(0,0,width, height);


// Render as normal here
// output goes to the FBO and it’s attached buffers

glPopAttrib();
glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);```
Three lines which probably jumped out at you right away are the glPushAttrib/glPopAttrib pair and the glViewport call. The glViewport call is needed so that we don’t try to render into an area bigger than, or even smaller than, the FBO is setup for. The glPushAtrrib and glPopAttrib are used as a quick way to save the old viewport information, this is needed because the FBO shares all of its states with the main context and as such any changes made affect both the FBO and the main context you would be normally rendering to.

An important point to make here is that you’ll notice that we only bound and then unbound the FBO to draw to it, we didn’t reattach any textures or renderbuffers, this because they stay attached until you detach them yourself or the FBO is destroyed.


####Using The Rendered To Texture

At this point our scene has been rendered to the texture and is now ready for us to use it and this operation itself is easy; we just bind the attached texture like any other texture.
```
glBindTexture(GL_TEXTURE_2D, img);```
Having carried that out the texture is now ready to read from as normal.

Depending on the texture’s filtering setup you might also want to generate mipmap information for it. Many people are used to using the gluBuild2DMipmaps() function to build mipmap information at load time and some of you might also be aware of the automatic mipmap generation extension; the FBO extension adds a third way with the GenerateMipmapEXT() function.

This function lets OpenGL build the mipmap information for you, the way it’s done depends on the hardware you are running on, and is the correct way to do so for textures you have rendered to (you shouldn’t use the automatic mipmap generation on a texture you are going to render to for various reasons which are covered in the spec).

To use the function all you have to do is bind a texture as above and then call:
```
glGenerateMipmapEXT(GL_TEXTURE_2D);```
OpenGL will then generate all the required mipmap data for you so that your texture is ready to be used.

It’s important to note that if you intend on using any of the mipmap filters (GL_LINEAR_MIPMAP_LINEAR for example) then you must call glGenerateMipmapEXT() before checking the framebuffer is complete or attempting to render to it.

At setup time you can just do it as follows:
```
glGenTextures(1, &img);
glBindTexture(GL_TEXTURE_2D, img);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glGenerateMipmapEXT(GL_TEXTURE_2D);```
At this point your texture is complete and can be rendered to like normal.

####Cleaning Up
Finally, when you are done with your FBO you need to clean things up and delete it. This, like textures, is done via a single function:
```
glDeleteFramebuffersEXT(1, &fbo);```
You also have to clean up any renderbuffers you might have allocated, in this case the depthbuffer renderbuffer needs to deleted, which again works the same way as cleaning up a texture:
```
glDeleteRenderbuffersEXT(1, &depthbuffer);```
At this point both the FBO and the renderbuffer have been freed and your clean up is completed.

####Final Thoughts

Hopefully this quick tour of the FBO extension will be enough to get you up and running with it. For a more detailed over view you'll want to check out the FBO spec or the section on the extension in the book More OpenGL Game Programming

In way of closing, before you go and check out the example program which shows a basic usage of the FBO extension I’d like to leave you with the following tips and notes on FBO usage.

- Currently you can’t have a stencil attachment. There is an extension in the works to allow for a texture format which would allow depth-stencil textures and thus render to stencil, however as of yet there is a lack of support for it.
- Don’t constantly make the destroy FBOs, instead generate what you need at load/setup time and reuse them during the program as required.
- Avoid modifying the texture you have rendered to via any glTexImage and related calls. Doing so can and most probably will hurt your performance.

####Notes on the example program

While this article talks about adding a depth renderbuffer and then a texture to the FBO in that order it was discovered that currently ATI’s drivers appear to have a bug whereby adding the depth renderbuffer and then a texture causes the application to crash. This should be kept in mind when doing any FBO related work and tested for as it is possible it could be fixed in a future driver revision thus rendering the problem non-existent.

I’d also like to put out a big thanks to Rick Appleton for helping me test out and debug the code on NVIDA hardware, couldn’t have done it without you mate :)

The example program requires some form of GLUT to be compiled and run (I used FreeGLUT)

[Source Code](http://downloads.gamedev.net/features/programming/fbo1/FBO_Example.zip)