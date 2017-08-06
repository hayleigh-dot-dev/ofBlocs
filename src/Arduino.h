#pragma once

#include "ofMain.h"
#include "ofSerial.h"

class Arduino {
private:
	ofSerial					arduino;

	vector<bool>                g;
    int                         size;
    
    const int                   width = 8;
    int                         height = 0;
public:
	Arduino();

	bool						setup(int port);
    
	void						update();
    
    void                        setPos(int i);
    void                        setPos(int x, int y);
};
