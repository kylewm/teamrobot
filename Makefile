export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
CC = g++
PACKAGES = clanCore-1.0 clanDisplay-1.0 clanApp-1.0 clanSound-1.0 clanGUI-1.0 clanGL-1.0 clanVorbis-1.0 clanGUIStyleSilver-1.0
CPPFLAGS = -O3 `pkg-config --cflags $(PACKAGES)`
LIBS = `pkg-config --libs $(PACKAGES)`
DEPS = 
OBJS=Block.o CabooseBot.o Enemy.o GameTile.o PushBot.o Sound.o Undeployed.o BombBot.o DecoyBot.o GameBoard.o GameUI.o Robot.o SwimBot.o WallCrawler.o BridgeBot.o DrillBot.o GameDisplay.o Moveable.o ShieldBot.o TurnBot.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

all: $(OBJS)
	$(CC) -o tr $(OBJS) $(LIBS)

clean:
	-rm -rf *.o
	-rm tr
