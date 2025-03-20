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

    Map/Box.cpp

    Menu.cpp
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

    Map/Box.hpp

    Menu.hpp
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
