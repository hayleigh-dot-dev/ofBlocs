#pragma once

#include "ofMain.h"
#include "ofSerial.h"

class Arduino {
private:
	ofSerial                    arduino;

	vector<bool>                grid;
    
    const int                   width = 8;
    const int                   height = 8;
public:
	Arduino();

	bool                        setup(int port, int baud);
    bool                        setup(string device, int baud);
    
	void                        update();
    
    void                        setPos(int i);
    void                        setPos(int x, int y);
    
    vector<bool>                getGrid();
};
