TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
        inGameDisplay.cpp \
        updateEtat.cpp \
        file.cpp \
        highscores.cpp \
        language.cpp \
        option.cpp \
        candycrush.cpp \
        controls.cpp \

HEADERS += \
        typeList.h \
        inGameDisplay.h \
        updateEtat.h \
        file.h \
        highscores.h \
        language.h \
        option.h \
        candycrush.h \
        controls.h \

DISTFILES += \
        lang/en.lang \
        lang/fr.lang \


