# **_MEOV_**

**Minimalistic Easy Object Viewer**: lightweight and easy-to-use 3D object viewer.

## **Scheme:**

```json
[
  {
    "name": "MainCamera",
    "type": "camera",
    "properties": {
      "transform": {
        "position": {
          "x": 0,
          "y": 0,
          "z": 0
        },
        "rotation": {
          "x": 0,
          "y": 0,
          "z": 0
        },
        "scale": {
          "x": 0,
          "y": 0,
          "z": 0
        }
      }
    }
  },
  {
    "name": "Model",
    "type": "node",
    "properties": {
      "transform": {
        "position": {
          "x": 0,
          "y": 0,
          "z": -10
        },
        "rotation": {
          "x": 0,
          "y": 0,
          "z": 0
        },
        "scale": {
          "x": 0,
          "y": 0,
          "z": 0
        }
      },
      "model": {
        "path": "path/to/object.obj"
      }
    }
  }
]
```

```mermaid
classDiagram
    direction LR

    class Core {
        +run() int
    }

    class SceneManager {
        +make(Window*, string path)
    }
    class Scene {
        +draw(Graphics *) void
        +update(float delta) void
    }
    class Node {
        +draw(Graphics *)* void
        +update(float delta)* void

        +getName() string
        +getProperty(string) Property
        +getChildren() vector~Node~
        +getChild(string name) Node
    }

    class Property

    class Window
    class Graphics {
        -mGlobalTransform matrix
        -mTransformQueue queue~matrix~
        -mColorQueue queue~color~

        +pushTransform(const matrix &transform) void
        +popTransform() void
        +pushColor(const Color &clr) void
        +popColor()

        +draw(const Model &model) void
        +draw(const Mesh &model) void
        +draw(const Texture &model) void
    }

    class Vertex
    class Shader
    class Texture
    class Mesh
    class Model
    class Sprite

    class Camera
    class ResourceManager

    Model o--> Mesh
    Model o--> Texture
    Model o--> Shader
    Mesh o--> "0..*" Vertex

    Property <|-- Model
    Property <|-- Transform
    Property <|-- Color

    Node o--> "2..*" Property
    Camera --|> Node

    Scene --|> Node

    SceneManager o--> "1..*" Scene

    Core o--> SceneManager
    Core o--> Window
    Core o--> Graphics


```

```cpp

meov::Core::Core()
    : mGraphics{ std::make_unique<Graphics>() }
{
    // initialize
}

int meov::Core::run() {
    Time timer;

    while(mWindow->isOpen()) {
        mScene->update(timer.getDelta());
        mWindow->update(timer.getDelta());

        mScene->render(mGraphics);
        mWindow->draw(mGraphics);
    }

    return 0;
}

```
