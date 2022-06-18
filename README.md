# C++ Table Tennis
Inspired by [**Twini-Golf**](https://polymars.itch.io/twini-golf) by Polymars, this project is a work in progress Table Tennis game made in SDL2 (C++).
This is my first C++ project ever and I made this game to learn the basics of the programming language. (may also contain a lot of memory leaks, but I don't know how to fix them)
<br>

## 📚 Libraries <hr>
This project takes advantage of the [**SDL2.0 (Simple DirectMedia Layer v2) Framework**](https://www.libsdl.org/) together with the extensions [**SDL_image**](http://wiki.libsdl.org/Libraries#sdl_image) and [**SDL_mixer**](http://wiki.libsdl.org/Libraries#sdl_mixer)
<br>

## 📦 Download <hr>
Program will later be released as a packaged program.
<br>

## 🔨 Building <hr>
1. Download and install SDL2.0
2. Download and install libraries / dependencies
    * SDL_image [(docs)](https://www.libsdl.org/projects/SDL_image/docs/index.html)
    * SDL_mixer [(docs)](https://www.libsdl.org/projects/SDL_mixer/docs/index.html)
    * SDL_ttf (not yet used) [(docs)](https://www.libsdl.org/projects/docs/SDL_ttf/)
3. Build the `CMakeLists.txt` with **cmake version 3.22.3** and link with **g++ (clang) version 13.0.0** *(clang-1300.0.27.3)*
4. The output will be located in `./cmake-build-default` together with the resources.
5. Run the application with `./TableTennis`
<br>

## Notes <hr>
* Because I'm using a retina display, the game may not be optimized for other displays. (The game calculates with only half the resolution, so on 'normal displays' the textures may only fill up a quarter of the screen).

## 🎯 Coming soon <hr>
* Start / Options menu
* Play against computer
* *multiplayer maybe maybe maybe...*
* Suitable logo
* Music
<br>

## 💡 Concept <hr>
The game uses a custom-made [**ECS (Entity Component System)**](https://en.wikipedia.org/wiki/Entity_component_system) which is very small in code size and does not require component signatures, multiple maps or registry. Every entity has one simple unordered map of components.

```cpp
std::unordered_map<const char*, Component*> components;
```

As you can see in the following code snippet, the key of the map is the typeid of the component and the value is the component itself. Also the entity with the newly added component gets returned, so you can use it to add other components in the same line of code.

```cpp
template<class T> Entity* addComponent(T *component) {
	this->components[typeid(*component).name()] = component;
	return this;
};
```

In order to get a component from an entity, we will upcast the base component to the derived class we want to have:

```cpp
template<class T> T* getComponent() {
	return dynamic_cast<T*>(
		components[typeid(T).name()]
	);
};
```

Components can also be removed from an entity by erasing the key (typeid) from the map.

```cpp
template<class T> Entity* removeComponent() {
	components.erase(typeid(T).name());
	return this;
};
```

<hr>

For rendering, I chose to use a spriteRenderer-component architecture on each of the entities that need to be displayed on the screen. Previously, I would have created an independant renderTarget instance for each entity, but this only led to problems when trying to interact with the renderTarget. With the component-based approach, it's very easy for the different scripts to communicate with each other.

```cpp
void SpriteRenderer::onInitialize() {
	transform = parent->getComponent<Transform>();
}

void SpriteRenderer::onStart() {
	printf("Loading Texture %s\n", img);
	texture = IMG_LoadTexture(renderer, img);
}

void SpriteRenderer::onUpdate() {
	SDL_Rect destrect; // [initialization...]
	SDL_RenderCopyEx(
		renderer, texture, &srcrect, &destrect, transform->getRotation(), transform->getAnchor(), SDL_FLIP_NONE
	);
}
```

> Note the use of the transform-component. This component stores position, rotation and scale to use in the rendering and calculations.