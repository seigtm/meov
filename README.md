<div align="center">

# **_MEOV_**

**Minimalistic Easy Object Viewer**: lightweight and easy-to-use 3D object viewer.

![GitHub](https://img.shields.io/github/license/seigtm/meov)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/seigtm/meov)
![GitHub Repo stars](https://img.shields.io/github/stars/seigtm/meov)
![GitHub top language](https://img.shields.io/github/languages/top/seigtm/meov)
![GitHub contributors](https://img.shields.io/github/contributors/seigtm/meov)

</div>


**‼️ Note**: this project is currently under development.

## **Diagrams:**

### `Named`, `Virtual` and `Component` classes diagram:

```mermaid
classDiagram
direction TB

Object --|> Holder
Object --|> Named

Holder "1" o--> "*" Component
Component "1" o..> "1" Holder : contains
Component <|-- TransformComponent
Component <|-- ModelComponent
Component <|-- LightingComponent

class Named {
    -string mName

    +Named(string&& name) ctor
    +Name() string
    +Rename(string&& name) void
}

class Component {
    <<virtual>>
    # weak_ptr~Holder~ mHolder

    +Component(string&& name) ctor
    +Draw()* void
    +Update(double)* void
    +Serialize()* void
    +SetHolder(weak_ptr~Holder~&& holder) void
}

class TransformComponent
class ModelComponent
class LightingComponent

class Holder {
    -GetTypeName()$ string
    -unordered_map~string, Component::Shared~ mComponents

    +GetComponent() T ptr
    +RemoveComponent() bool
    +AddComponent(Args&&... args) T ptr
    +ForEachComponent(function~void(Component::Shared&)~&& method)
}

class Object {
    <<virtual>>
    +Object(string&& name) ctor
    +Draw(Graphics& g)* void
    +Update(double delta)* void
    +Serialize()* void
}

```

### (OLD) Main scene things diagram:

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

    class Vertex {
        +position vec4
        +color vec4
        +texturePosition vec2
        +tangent vec3
        +bitAgent vec3
    }
    class Shader {
    }
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

## (Not implemented) JSON configuration file example:

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
