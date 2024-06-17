# OpenGL Rendering Engine

This project is an OpenGL-based rendering engine that demonstrates the use of modern OpenGL features for rendering 2D textures and managing various OpenGL objects like shaders, buffers, and textures. The project is structured into several classes to handle different aspects of rendering, including vertex buffers, index buffers, shaders, textures, and vertex arrays.

## Table of Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Classes](#classes)
  - [Renderer](#renderer)
  - [Shader](#shader)
  - [Texture](#texture)
  - [VertexArray](#vertexarray)
  - [VertexBuffer](#vertexbuffer)
  - [IndexBuffer](#indexbuffer)
  - [VertexBufferLayout](#vertexbufferlayout)
- [Dependencies](#dependencies)

## Requirements

- C++17 or later
- OpenGL 3.3 or later
- CMake 3.10 or later

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/lfeq/Motor
    cd Motor
    ```

2. Initialize and update submodules (if any):
    ```sh
    git submodule update --init --recursive
    ```

3. Create a build directory and run CMake:
    ```sh
    mkdir build
    cd build
    cmake ..
    ```

4. Build the project:
    ```sh
    make
    ```

---

### NOTE
You can also open it with Visual Studio 2022, just open the OpenGL.sln file and make sure it's solution platform is set to x86 and **NOT** x64.

## Usage

Run the executable generated in the build directory:
```sh
./OpenGLRenderer
```

## Classes

### Renderer
The Renderer `class` encapsulates the drawing operations and error handling for OpenGL calls.

``` c++
class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
```

### Shader

The `Shader` class handles the compilation and management of vertex and fragment shaders.

```c++
class Shader {
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    int GetUniformLocation(const std::string& name);
};
```

### Texture

The `Texture` class handles the loading and binding of 2D textures.

```c++
class Texture {
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

private:
    unsigned int m_rendererID;
    std::string m_filepath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_BPP;
};
```

### VertexArray

The `VertexArray` class manages vertex array objects (VAOs).

```c++
class VertexArray {
public:
    VertexArray();
    ~VertexArray();
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;
};
```

### VertexBuffer
The `VertexBuffer` class manages vertex buffer objects (VBOs).

```c++
class VertexBuffer {
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};
```

### IndexBuffer

The `IndexBuffer` class manages index buffer objects (IBOs).

```c++
class IndexBuffer {
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_count; }
};
```

### VertexBufferLayout

The `VertexBufferLayout` class defines the layout of vertex buffer data.

```c++
class VertexBufferLayout {
public:
    VertexBufferLayout();

    template<typename T>
    void Push(unsigned int count);

    inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }
    inline unsigned int GetStride() const { return m_stride; }

private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
};
```

## Dependencies
- GLEW
- GLFW
- glm
- stb_image