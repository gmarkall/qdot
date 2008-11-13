#############################################################################
# Makefile for building: QDot
# Generated by qmake (2.01a) (Qt 4.3.3) on: gio nov 13 18:06:05 2008
# Project:  QDot.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile QDot.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Iinclude -Itmp -Itmp
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib64/qt4 -lQtGui -L/usr/lib64 -L/usr/lib64/qt4 -L/usr/lib -lpng -lSM -lICE -lXrender -lXrandr -lXfixes -lXcursor -lXinerama -lfreetype -lfontconfig -lXext -lX11 -lQtCore -lz -lm -lrt -ldl -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = tmp/

####### Files

SOURCES       = src/DotEdit.cpp \
		src/main.cpp \
		src/MainWin.cpp \
		src/DotElement.cpp \
		src/AddElementWin.cpp \
		src/AssociateElementWin.cpp tmp/moc_DotEdit.cpp \
		tmp/moc_MainWin.cpp \
		tmp/moc_DotElement.cpp \
		tmp/moc_AddElementWin.cpp \
		tmp/moc_AssociateElementWin.cpp \
		qrc_resource.cpp
OBJECTS       = tmp/DotEdit.o \
		tmp/main.o \
		tmp/MainWin.o \
		tmp/DotElement.o \
		tmp/AddElementWin.o \
		tmp/AssociateElementWin.o \
		tmp/moc_DotEdit.o \
		tmp/moc_MainWin.o \
		tmp/moc_DotElement.o \
		tmp/moc_AddElementWin.o \
		tmp/moc_AssociateElementWin.o \
		tmp/qrc_resource.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		QDot.pro
QMAKE_TARGET  = QDot
DESTDIR       = 
TARGET        = QDot

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): tmp/ui_MainWin.h tmp/ui_About.h tmp/ui_AddElementWin.h tmp/ui_AssociateElementWin.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: QDot.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib64/qt4/libQtGui.prl \
		/usr/lib64/qt4/libQtCore.prl
	$(QMAKE) -unix -o Makefile QDot.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib64/qt4/libQtGui.prl:
/usr/lib64/qt4/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile QDot.pro

dist: 
	@$(CHK_DIR_EXISTS) tmp/QDot1.0.0 || $(MKDIR) tmp/QDot1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) tmp/QDot1.0.0/ && $(COPY_FILE) --parents include/DotEdit.h include/MainWin.h include/DotElement.h include/AddElementWin.h include/AssociateElementWin.h tmp/QDot1.0.0/ && $(COPY_FILE) --parents resource.qrc tmp/QDot1.0.0/ && $(COPY_FILE) --parents src/DotEdit.cpp src/main.cpp src/MainWin.cpp src/DotElement.cpp src/AddElementWin.cpp src/AssociateElementWin.cpp tmp/QDot1.0.0/ && $(COPY_FILE) --parents ui/MainWin.ui ui/About.ui ui/AddElementWin.ui ui/AssociateElementWin.ui tmp/QDot1.0.0/ && (cd `dirname tmp/QDot1.0.0` && $(TAR) QDot1.0.0.tar QDot1.0.0 && $(COMPRESS) QDot1.0.0.tar) && $(MOVE) `dirname tmp/QDot1.0.0`/QDot1.0.0.tar.gz . && $(DEL_FILE) -r tmp/QDot1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: tmp/moc_DotEdit.cpp tmp/moc_MainWin.cpp tmp/moc_DotElement.cpp tmp/moc_AddElementWin.cpp tmp/moc_AssociateElementWin.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) tmp/moc_DotEdit.cpp tmp/moc_MainWin.cpp tmp/moc_DotElement.cpp tmp/moc_AddElementWin.cpp tmp/moc_AssociateElementWin.cpp
tmp/moc_DotEdit.cpp: include/DotElement.h \
		include/DotEdit.h
	/usr/bin/moc $(DEFINES) $(INCPATH) include/DotEdit.h -o tmp/moc_DotEdit.cpp

tmp/moc_MainWin.cpp: tmp/ui_MainWin.h \
		tmp/ui_About.h \
		include/DotEdit.h \
		include/DotElement.h \
		include/MainWin.h
	/usr/bin/moc $(DEFINES) $(INCPATH) include/MainWin.h -o tmp/moc_MainWin.cpp

tmp/moc_DotElement.cpp: include/DotElement.h
	/usr/bin/moc $(DEFINES) $(INCPATH) include/DotElement.h -o tmp/moc_DotElement.cpp

tmp/moc_AddElementWin.cpp: tmp/ui_AddElementWin.h \
		include/DotElement.h \
		include/AddElementWin.h
	/usr/bin/moc $(DEFINES) $(INCPATH) include/AddElementWin.h -o tmp/moc_AddElementWin.cpp

tmp/moc_AssociateElementWin.cpp: include/DotElement.h \
		include/DotEdit.h \
		tmp/ui_AssociateElementWin.h \
		include/AssociateElementWin.h
	/usr/bin/moc $(DEFINES) $(INCPATH) include/AssociateElementWin.h -o tmp/moc_AssociateElementWin.cpp

compiler_rcc_make_all: qrc_resource.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resource.cpp
qrc_resource.cpp: resource.qrc \
		images/logo.png \
		images/icon.png
	/usr/bin/rcc -name resource resource.qrc -o qrc_resource.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: tmp/ui_MainWin.h tmp/ui_About.h tmp/ui_AddElementWin.h tmp/ui_AssociateElementWin.h
compiler_uic_clean:
	-$(DEL_FILE) tmp/ui_MainWin.h tmp/ui_About.h tmp/ui_AddElementWin.h tmp/ui_AssociateElementWin.h
tmp/ui_MainWin.h: ui/MainWin.ui
	/usr/bin/uic ui/MainWin.ui -o tmp/ui_MainWin.h

tmp/ui_About.h: ui/About.ui
	/usr/bin/uic ui/About.ui -o tmp/ui_About.h

tmp/ui_AddElementWin.h: ui/AddElementWin.ui
	/usr/bin/uic ui/AddElementWin.ui -o tmp/ui_AddElementWin.h

tmp/ui_AssociateElementWin.h: ui/AssociateElementWin.ui
	/usr/bin/uic ui/AssociateElementWin.ui -o tmp/ui_AssociateElementWin.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

tmp/DotEdit.o: src/DotEdit.cpp include/DotEdit.h \
		include/DotElement.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/DotEdit.o src/DotEdit.cpp

tmp/main.o: src/main.cpp include/MainWin.h \
		tmp/ui_MainWin.h \
		tmp/ui_About.h \
		include/DotEdit.h \
		include/DotElement.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/main.o src/main.cpp

tmp/MainWin.o: src/MainWin.cpp include/MainWin.h \
		tmp/ui_MainWin.h \
		tmp/ui_About.h \
		include/DotEdit.h \
		include/DotElement.h \
		include/AddElementWin.h \
		tmp/ui_AddElementWin.h \
		include/AssociateElementWin.h \
		tmp/ui_AssociateElementWin.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/MainWin.o src/MainWin.cpp

tmp/DotElement.o: src/DotElement.cpp include/DotElement.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/DotElement.o src/DotElement.cpp

tmp/AddElementWin.o: src/AddElementWin.cpp include/AddElementWin.h \
		tmp/ui_AddElementWin.h \
		include/DotElement.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/AddElementWin.o src/AddElementWin.cpp

tmp/AssociateElementWin.o: src/AssociateElementWin.cpp include/AssociateElementWin.h \
		include/DotElement.h \
		include/DotEdit.h \
		tmp/ui_AssociateElementWin.h \
		include/AddElementWin.h \
		tmp/ui_AddElementWin.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/AssociateElementWin.o src/AssociateElementWin.cpp

tmp/moc_DotEdit.o: tmp/moc_DotEdit.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_DotEdit.o tmp/moc_DotEdit.cpp

tmp/moc_MainWin.o: tmp/moc_MainWin.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_MainWin.o tmp/moc_MainWin.cpp

tmp/moc_DotElement.o: tmp/moc_DotElement.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_DotElement.o tmp/moc_DotElement.cpp

tmp/moc_AddElementWin.o: tmp/moc_AddElementWin.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_AddElementWin.o tmp/moc_AddElementWin.cpp

tmp/moc_AssociateElementWin.o: tmp/moc_AssociateElementWin.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_AssociateElementWin.o tmp/moc_AssociateElementWin.cpp

tmp/qrc_resource.o: qrc_resource.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/qrc_resource.o qrc_resource.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

