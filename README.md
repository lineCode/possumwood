## Synopsis

![Possumwood UI](doc/possumwood_half.gif?raw=true)

Possumwood (named after [Sandbox Tree](https://en.wikipedia.org/wiki/Hura_crepitans)) is a **graph-based procedural sandbox**, implementing concepts of graph-based [visual programming](https://en.wikipedia.org/wiki/Visual_programming_language) in a simple interface. It is intended to provide a user-friendly and accessible UI for experimenting with common computer graphics algorithms and libraries (e.g., [CGAL](http://www.cgal.org/), [WildMagic](https://www.geometrictools.com/), [Eigen](http://eigen.tuxfamily.org/), [PhysBam](http://physbam.stanford.edu/)).

Possumwood is built on top of a simple graph-evaluation engine and a Qt-based node graph editor, with an OpenGL viewport. Its main strength is its extensibility - it is trivial to implement new plugins supporting new libraries and data types, which allows free and user-friendly experimentation with parameters of each algorithm.

**Possumwood is a sandbox, not a production tool.** As a sandbox, it is quite open to radical changes and redesign, and for the time being it does not guarantee any form backwards compatibility.

[![Build Status](https://travis-ci.org/martin-pr/possumwood.svg?branch=master)](https://travis-ci.org/martin-pr/possumwood)

## Tutorials

Tutorials are intended to introduce the concepts in Possumwood, and help a user navigate its UIs. They are still work-in-progress, and more will be added over time.

### OpenGL / GLSL

#### [GLSL Turntable](https://github.com/martin-pr/possumwood/wiki/Basics-of-GLSL-in-Possumwood)

<img src="doc/tutorial_opengl_01.gif" align="right" width="150">

Introduces basic concepts of GLSL shaders in Possumwood, via a simple setup displaying a rotating car. Its model is loaded from an `.obj` file, converted to an OpenGL Vertex Buffer Object and displayed using a combination of a vertex and a fragment shader.

<div style="clear: both"></div>

#### [Skybox](https://github.com/martin-pr/possumwood/wiki/Skybox)

<img src="doc/skybox.png" align="right" width="150">

A simple GLSL skybox setup, using fragment shader and the `background` node (based on [gluUnProject](https://www.khronos.org/registry/OpenGL-Refpages)) to render a background quad with spherically-mapped texture.

<div style="clear: both"></div>

#### [Environment mapping](https://github.com/martin-pr/possumwood/wiki/Environment-mapping)

<img src="doc/envmap.png" align="right" width="150">

Environment map is a simple technique to approximate reflective surfaces in GLSL, without the need of actual raytracing. This tutorial builds on the previous Skybox tutorial, and extends it to make a teapot's material tool like polished metal.

<div style="clear: both"></div>

#### [Wireframe using a geometry shader](https://github.com/martin-pr/possumwood/wiki/Wireframe-using-a-Geometry-Shader)

<img src="doc/wireframe.png" align="right" width="150">

Most implementation of OpenGL 4 remove the ability to influence the width of lines using the classical `glLineWidth` call. This tutorial describes in detail how to achieve a similar effect (and much more) using a geometry shader, by rendering each line as a camera-facing polygon strip.

<div style="clear: both"></div>

#### [PN Triangles Tesselation using a geometry shader](https://github.com/martin-pr/possumwood/wiki/Geometry-Shader-Tessellation-using-PN-Triangles)

<img src="doc/pn_triangles.png" align="right" width="150">

Implementation of [Curved PN Triangles](https://alex.vlachos.com/graphics/CurvedPNTriangles.pdf) tessellation technique, presented by Alex Vlachos on GDC 2011. This method tessellates input triangles using solely their vertex positions and normals (independently of the mesh topology) in a geometry shader.

<div style="clear: both"></div>

#### [Infinite Ground Plane using GLSL Shaders](https://github.com/martin-pr/possumwood/wiki/Infinite-ground-plane-using-GLSL-shaders)

<img src="doc/ground_plane.png" align="right" width="150">

Infinite ground plane, implemented using a single polygon and simple fragment shader "raytracing" against a plane with _Y=0_.

<div style="clear: both"></div>

#### [Phong reflectance and shading models](https://github.com/martin-pr/possumwood/wiki/Phong-Lighting-Model)

<img src="doc/phong.png" align="right" width="150">

The [Phong reflectance model](https://en.wikipedia.org/wiki/Phong_reflection_model), and [Phong shading](https://en.wikipedia.org/wiki/Phong_shading) are two basic models of light behaviour in computer graphics. This tutorial explains their function, and provides a step-by-step implementation in GLSL, using a single orbiting light as the lightsource.


## Code Example

Possumwood is designed to be easily extensible. A simple addition node, using float attributes, can be implemented in a few lines of code:

```cpp
#include <possumwood_sdk/node_implementation.h>

namespace {

// strongly-typed attributes
dependency_graph::InAttr<float> input1, input2;
dependency_graph::OutAttr<float> output;

// main compute function
dependency_graph::State compute(dependency_graph::Values& data) {
	// maintains attribute types
	const float a = data.get(input1);
	const float b = data.get(input2);

	data.set(output, a + b);

	// empty status = no error (both dependency_graph::State and exceptions are supported)
	return dependency_graph::State();
}

void init(possumwood::Metadata& meta) {
	// attribute registration
	meta.addAttribute(input1, "a");
	meta.addAttribute(input2, "b");
	meta.addAttribute(output, "out");

	// attribute dependencies
	meta.addInfluence(input1, output);
	meta.addInfluence(input2, output);

	// and setting up a compute method
	meta.setCompute(compute);
}

// static registration of a new node type
possumwood::NodeImplementation s_impl("maths/add", init);

}
```

## Installation

The project is structured as a standard CMake-built project. To build, just run these in the directory of the repository on any Linux distro:

```
mkdir build
cd build
cmake .. && make -j
```

No installation targets are provided for the time being.

The code has been tested only on Linux (several distributions). While it should fundamentally work on Windows, it has not been compiled there. No support for MacOS is planned for the time being due to heavy dependency on OpenGL.

## API Reference

An auto-generated Doxygen reference can be found [here](https://martin-pr.github.io/possumwood/annotated.html)

## Contributors

Please feel free to contribute! I would welcome any form of feedback, opinions, bugs, code, or description of projects you are planning to use my code in!

At the moment, the project is in its **prototype stage**, and any feedback or help is welcome. In particular, it is in dire need of **a MS Windows build**, preferably using **AppVeyor**. Any help in that area would be greatly appreciated!

## License

The code is released under the [MIT license](https://en.wikipedia.org/wiki/MIT_License).
