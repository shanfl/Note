##OpenGL FrameBuffer Object 201
by Rob phantom Jones
[source code](http://downloads.gamedev.net/features/programming/fbo2/FBO_Example2.zip)

----

[toc]

####Introduction
In the last OpenGL Framebuffer object article we covered the basic usage of an FBO for rendering to a single texture and then applying that texture some where else. However this isn’t all the FBO extension can do; indeed one of the integrated features of this extension which was touched upon briefly in the last article was that of attachment points.

In this article we’ll go a little more in-depth into this aspect of the extension, first of all showing how you can use a single FBO to cycle through a number of textures to render to and finish off with using the OpenGL Shading Language to render to multiple textures at the same time via the Draw Buffers extension.

####One FBO and Many Textures
In the last article we covered how to attach a texture to an FBO as a colour render target using the following function call:
```
glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img, 0);
```
As you might recall, the function attaches the texture indicated by the value held in img to the currently bound FBO. In this article the point of interest is the second parameter: **GL_COLOR_ATTACHMENT0_EXT**.

As you might recall, the function attaches the texture indicated by the value held in img to the currently bound FBO. In this article the point of interest is the second parameter: **GL_COLOR_ATTACHMENT0_EXT**.

This parameter tells OpenGL to attach the texture to attachment point 0, however FBOs have many more colour attachment points which can be bound. The current specification allows for 16 attachment points (GL_COLOR_ATTACHMENT0_EXT to GL_COLOR_ATTACHMENT15_EXT) each of which can point to a separate texture attached to it. However, the number you can render to depends on whether you are running on hardware and drivers; this can be queried using the following code:

```
GLuint maxbuffers;
glGetIntergeri(GL_MAX_COLOR_ATTACHMENTS, &maxbuffers);
```

At this point maxbuffers holds the total number of colour attachments you can attach. On current hardware available at the time of writing the value returned will be a max of 4 buffers.

So, if we wanted to attach the texture indicated by img to the 2nd colour attachment point the above function call would become:
```
glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, img, 0);
```
As you can see it is pretty easy to add textures, but how do we tell OpenGL where to render to?

####Selecting The Destination
Well, in this case we go back to a function which has been around since the start of OpenGL; glDrawBuffer()

This function, and its relative glReadBuffer(), tells OpenGL where it should write data to and where it should read data from. By default both the draw and read buffers are set as GL_FRONT for single buffered contexts and GL_BACK for double buffered ones. With the advent of the FBO extension this function has been modified to allow you to select GL_COLOR_ATTACHMENTx_EXT for rendering to and reading from (where ‘x’ is the attachment point number).

When you bind an FBO, the buffers are changed behind your back to GL_COLOR_ATTACHMENT0_EXT. So if you are only rendering to the default colour attachment point you don’t have to make any changes, however when it comes to other buffers we have to tell OpenGL ourselves where we want it to render to.

Thus if we want to render to GL_COLOR_ATTACHMENT1_EXT we would have to bind the FBO and set the write buffer to the correct attachment point. Assuming we have attached a texture to colour attachment point 1 for the FBO held in fbo, then rendering would look as follows:
```
glBindFrameBuffer(GL_FRAMEBUFFER_EXT, fbo);
glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT);
glViewport(0,0,width, height);

// Set the render target
glDrawBuffer(GL_COLOR_ATTACHMENT1_EXT);

// Render as normal here
// output goes to the FBO and it’s attached buffers


glPopAttrib();
glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
```

Note the use of glPushAttrib() to save both the viewport and colour buffer configuration before we make the changes and the use of glPopAttrib() to restore them once we are done. This is because these changes affect both the FBO and main rendering context and we don’t want them active once we have completed rendering to the texture.

An important point when attaching multiple textures to an FBO is that they all have to be of the same dimension and colour depth. So, you can’t attach a 512*512 32bit texture and a 256*256 16bit texture to the same FBO. However if you can stay within these limits then it is possible to use one FBO to render to multiple textures, which is faster than switching between FBOs. While this isn’t an overly slow operation, avoiding unneeded operations is often good practise.

####The first example
The first example program gives an example of rendering to 2 textures, one after each other, and then applying those textures to another cube. The code is based on the same example as used in the first article; there are some minor changes however.

Firstly, in the FBO setup code in the init function we create and bind a second texture to the FBO we created. Notice how we bind it to different attachment point to the first texture by using GL_COLOR_ATTACHMENT1_EXT as the bind point.

The rendering for the scene is basically the same as well, however instead of drawing the cube with its colours on once we draw it twice, the second time with the colours at half the intensity.

You should notice in the example program that when we render to the FBO we explicitly tell OpenGL to render to GL_COLOR_ATTACHMENT0_EXT and then GL_COLOR_ATTACHMENT1_EXT; this is because the FBO remembers the last buffer you told it to draw to, so when the drawing loop runs for the second time the first texture isn’t updated as the drawing goes to the destination given in the last glDrawBuffer() call, which in this case is GL_COLOR_ATTACHMENT1_EXT. To see this effect comment out line 133, which has the glDrawBuffer() call in it, and you will notice the texture on the left hand cube is never updated.

####Multiple Render Targets
Now we know how to attach multiple textures to an FBO, however we are still only drawing to one texture at a time by switching the draw target and, as helpful as that might be, at the start of the article it was mentioned that we would be covering how to render to multiple textures at the same time.

Well, it turns out that once you understand how to attach multiple textures at once the rest is pretty simple and all you need comes from the Draw Buffers extension and the OpenGL Shading Language (GLSL), both of which are core features of OpenGL 2.0.

####The Draw Buffers Extension

The first extension, Draw Buffers, builds upon the functionality provided by glDrawBuffer(). As you recall this function allows us to specify which colour buffer we are going to write to, the Draw Buffers extension expands upon this to allow us to specify multiple colour buffers to write to. The number of buffers you can render to at once can be queried as follows:
```
GLuint maxbuffers;
glGetIntergeri(GL_MAX_DRAW_BUFFERS, &maxbuffers);
```
After which the variable maxbuffers holds the number of buffers we can render to at once (at the time of writing this value is typically 4, however the GeForce 8x00 series allows for up to 8 buffers to be drawn to).

The function used to indicated which buffers to draw to takes the same values as the glDrawBuffer() for the targets, which means we can supply it with GL_COLOR_ATTACHMENTx_EXT values in order to write to multiple attached textures at the same time.

Thus if we had textures attached to points 0 and 1, and wanted to render to both of them then we would do the following:
```
GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
glDrawBuffers(2, buffers);
```
After this function is executed OpenGL is setup to render to both colour buffers, which brings us on to how this is done.

####MRT with FBO and GLSL
At this point if we were to render it using the standard Fixed Function Pipeline (as the examples have used thus far) then both textures would get the same data in them, however using GLSL we can write a fragment shader which allows us to send different data to the textures.

Normally when you write a GLSL fragment shader you would output the colour value to gl_FragColor, which would then be written to the frame buffer as normal. However there is a second way to write out colour information via the gl_FragData[] array.

This special variable allows us to direct where the data is going and maps directly to the values given to glDrawBuffers(). So, in the case of the glDrawBuffers() call above the buffers would map as follows:

| glDrawBuffers value            |      FragData syntax |
|--------------------------------|----------------------|
|   GL_COLOR_ATTACHMENT0_EXT     |    gl_FragData[0]    |
|   GL_COLOR_ATTACHMENT1_EXT     |    gl_FragData[1]    |


If we were to change the above function call however the mappings would change:
```
GLenum buffers[] = { GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT0_EXT };
glDrawBuffers(2, buffers);
```
| glDrawBuffers value            |      FragData syntax |
|--------------------------------|----------------------|
|   GL_COLOR_ATTACHMENT1_EXT     |    gl_FragData[0]    |
|   GL_COLOR_ATTACHMENT0_EXT     |    gl_FragData[1]    |

This is highlighted because it is the order the values are supplied to the glDrawBuffers() function, which dictates how they map to the gl_FragData[] array, not their values.

Lets say that for some reason we wanted to write green to one render target and blue to the other, then the GLSL code would look as follows:
```
#version 110

void main()
{
	gl_FragData[0] = vec4(0.0, 1.0, 0.0);
	gl_FragData[1] = vec4(0.0, 0.0, 1.0);
}
```
The first line says we need at least version 1.10 (OGL2.0) of the GLSL and the function body just writes green to the first buffer and blue to the second buffer.

####The Second Example

The second example is a hybrid of the first example and the example from the first article. It performs the same output as the first example from this article but only draws the cube to the FBO once like the original article does; we achieve this by using a shader to control the output.

As with before, the major difference is in the initialisation code. Leaving aside the loading of a GLSL program, which is beyond the scope of this article, the part which is required to make MRT rendering work with an FBO is the following two lines:
```
GLenum mrt[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT }
glDrawBuffers(2, mrt);
```
These two lines tell OpenGL that we wish to render to two buffers and what those two buffers are. Remember that an FBO remembers the last render target it was told to use, as such by doing this while the FBO is bound we can set this at startup and not have to worry about doing so during the main rendering loop.

The rendering loop should look familiar; the rendering to the FBO is the same as the original code, the only change being the call to bind and unbind the GLSL program which controls the colour output. The lower section is the same as the first example from this article, with the two cubes being rendered one with each texture on it.

The two GLSL shaders themselves require a quick mention as they are somewhat central to how MRT works in this manner.

The vertex shader, which is executed for each vertex you send to the graphics card, simply passes the colour value passed via glColor() to the fragment shader and transforms the vertex so it will be in the right place to draw the cube.

The fragment shader used is as follows:
```
#version 110

void main(void)
{
	gl_FragData[0] = vec4(gl_Color.r, gl_Color.g,gl_Color.b,1.0);
	gl_FragData[1] = vec4(gl_Color.r/2.0, gl_Color.g/2.0,gl_Color.b/2.0,1.0);
}
```
The key lines are the two gl_FragData lines, these indicate which buffer we are writing to. In this case **gl_FragData[0]** is the first texture and it gets a copy of the unmodified colour passed down from the vertex. On the other hand **gl_FragData[1]** is the second texture and gets the value of the colour passed from the vertex shader but halfed, thus giving the same output as the first example.


####Final Thoughts

This article was designed to give you a quick overview and example of two more uses of the FBO extension.

The first example allows you to use the same FBO to render to multiple textures without switching FBOs, this is a useful thing to know because while FBOs are light to change when compared to pbuffers it is still much quicker to switch render targets than to switch between FBOs. As such if you can group your textures which need to be rendered to one at a time in such a way you can save some time.

The second example was to give you a feel for MRT rendering. While the example here is somewhat trivial, MRT does form a major part of various render-to-vertex buffer and post-processing techniques, as such the ability to output to multiple colour buffers is a useful one to know.

As before more details can be found in the Framebuffer Object spec and the Draw Buffers spec. More OpenGL Game Programming also has a chapter on FBOs and a chapter on GLSL, written by myself, which touches on using FBOs and MRT with GLSL some more.