## OpenGL-Learning

* 介绍: 个人的OpenGL学习记录，参考[LearnOpenGL-CN](https://learnopengl-cn.github.io/)，并为此搭建相应的框架支持
* 语言: C++11
* 编译器: Clang
* 工程部署: CMake
* 平台: macOS

### Roadmap
* [Hello Triangle](https://github.com/MusouCrow/OpenGL-Learning/tree/Hello-Triangle): 基于[本篇](https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/)，实现了一个三角形的显示
* [Triangle & Quad](https://github.com/MusouCrow/OpenGL-Learning/tree/TriangleNQuad): 基于[本篇](https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/)，在三角形的基础上加入了四边形
* [Shaders](https://github.com/MusouCrow/OpenGL-Learning/tree/Shaders): 基于[本篇](https://learnopengl-cn.github.io/01%20Getting%20started/05%20Shaders/)，封装了Shader类
* [Textures](https://github.com/MusouCrow/OpenGL-Learning/tree/Textures): 基于[本篇](https://learnopengl-cn.github.io/01%20Getting%20started/06%20Textures/)，封装了Texture类，实现了贴图效果
* [Transformations](https://github.com/MusouCrow/OpenGL-Learning/tree/Transformations): 基于[本篇](https://learnopengl-cn.github.io/01%20Getting%20started/07%20Transformations/)，封装了Transform类，实现了变换效果（位置、缩放、旋转）
* [Camera](https://github.com/MusouCrow/OpenGL-Learning/tree/Camera): 基于[坐标系统](https://learnopengl-cn.github.io/01%20Getting%20started/08%20Coordinate%20Systems/)与[摄像机](https://learnopengl-cn.github.io/01%20Getting%20started/09%20Camera/)，封装了Camera类，实现了镜头变换，配合实现了多物件渲染、深度测试、背面剔除