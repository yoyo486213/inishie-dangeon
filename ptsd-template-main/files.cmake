set(SRC_FILES
    App.cpp
    MyBGM.cpp
    Character.cpp
    AnimatedCharacter.cpp
    Map/Map.cpp
    Map/InvisibleWall.cpp
    Map/Unexplored.cpp
    Map/Door.cpp
    Map/Chest.cpp
    Map/UpStairs.cpp
    Map/DownStairs.cpp
    Map/DestructibleObject.cpp

    Map/Box.cpp

    Monster/Monster.cpp
    Monster/Rat.cpp
    Monster/Snake.cpp
    Monster/Bat.cpp
    Monster/Worm.cpp
    Monster/Slime.cpp
    Monster/Zombie.cpp

    Player.cpp

    Menu.cpp
    Text.cpp
    Menus/CreateCharacterMenu.cpp
    Menus/StartMenu.cpp
    Button.cpp
    Buttons/NewGameButton.cpp
    Buttons/NameKeyBoard.cpp
    MoveAnimated.cpp
)

set(INCLUDE_FILES
    IClickable.hpp
    IMoveable.hpp
    App.hpp
    MyBGM.hpp
    Character.hpp
    AnimatedCharacter.hpp
    Map/Map.hpp
    Map/InvisibleWall.hpp
    Map/Unecplored.hpp
    Map/Door.hpp
    Map/Chest.hpp
    Map/UpStairs.hpp
    Map/DownStairs.hpp
    Map/DestructibleObject.hpp

    Map/Box.hpp

    Monster/Monster.hpp
    Monster/Rat.hpp
    Monster/Snake.hpp
    Monster/Bat.hpp
    Monster/Worm.hpp
    Monster/Slime.hpp
    Monster/Zombie.hpp

    Player.hpp

    Menu.hpp
    Text.hpp
    Menus/CreateCharacterMenu.hpp
    Menus/StartMenu.hpp
    nolohmann/json_fwd.hpp
    nolohmann/json.hpp
    Button.hpp
    Buttons/NewGameButton.hpp
    Buttons/NameKeyBoard.hpp
    MoveAnimated.hpp
)

set(TEST_FILES
)
