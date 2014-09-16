cocosdl
=======

CocosDL is a cocos2d-x inspired game framework built on top of libSDL2.
It, however, hides libSDL2 from the framework end user to make it as portable as possible.
I have already created some test games with it that I will soon publish as an example, but
keep in mind that this is still a 0.1 release.
That means that it is not optimized, has not all the features I would like, and possibly has
some bugs.

The framework already has a base Node class and the basic subclasses needed for simple games:
Scene, Sprite, Label, Button.
It also has a good catalog of basic actions to add visual effects to your games, such as
Rotation, Fading, Scaling, Sound effects, Sequences, Groups, etc.

It has currently been tested on Mac OSX, and it comes with an Xcode 5 project with the
framework targets (static library, dynamic library and framework) and a small test project.
You can play with it easily from Xcode.

The good thing about it is that it should work on any platform libSDL2 works on: Mac OSX, Windows,
Android, iOS and Linux.


