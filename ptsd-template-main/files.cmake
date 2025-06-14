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

    Items/Item.cpp
    Items/Potion.cpp
    Items/Orb.cpp

    Weapon/Weapon.cpp
    Weapon/SortSword.cpp
    Weapon/Bow.cpp
    Weapon/Buckler.cpp
    Weapon/FireRod.cpp
    Weapon/IceRod.cpp
    Weapon/HunterBow.cpp
    Weapon/Club.cpp
    Weapon/Dagger.cpp
    Weapon/HandAx.cpp
    Weapon/Dark.cpp
    Weapon/Mace.cpp

    Monster/Monster.cpp
    Monster/Rat.cpp
    Monster/Snake.cpp
    Monster/Bat.cpp
    Monster/Worm.cpp
    Monster/Slime.cpp
    Monster/Zombie.cpp
    Monster/Skeleton.cpp
    Monster/Mage.cpp
    Monster/Ghoul.cpp

    Player.cpp

    Menu.cpp
    Text.cpp
    Menus/CreateCharacterMenu.cpp
    Menus/PlayerUI.cpp
    Menus/StartMenu.cpp
    Button.cpp
    Buttons/NewGameButton.cpp
    Buttons/NameKeyBoard.cpp
    MoveAnimated.cpp
)

set(INCLUDE_FILES
    IClickable.hpp
    ICollidable.hpp
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

    Items/Item.hpp
    Items/Potion.hpp
    Items/Orb.hpp

    Weapon/Projectile.hpp
    Weapon/Weapon.hpp
    Weapon/SortSword.hpp
    Weapon/Bow.hpp
    Weapon/Buckler.hpp
    Weapon/FireRod.hpp
    Weapon/IceRod.hpp
    Weapon/HunterBow.hpp
    Weapon/Club.hpp
    Weapon/Dagger.hpp
    Weapon/HandAx.hpp
    Weapon/Dark.hpp
    Weapon.Mace.hpp

    Monster/Monster.hpp
    Monster/Rat.hpp
    Monster/Snake.hpp
    Monster/Bat.hpp
    Monster/Worm.hpp
    Monster/Slime.hpp
    Monster/Zombie.hpp
    Monster/Skeleton.hpp
    Monster/Mage.hpp
    Monster/Ghoul.hpp

    Player.hpp

    Menu.hpp
    Text.hpp
    Menus/CreateCharacterMenu.hpp
    Menus/PlayerUI.hpp
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
