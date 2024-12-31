#include "GraphicExample.h"

std::vector<WindowInfo> DX11::GraphicExample::mWindowInfos;
std::vector<DX11::sptrAdapter> *DX11::GraphicExample::mAdapters;
DX11::sptrDevice DX11::GraphicExample::mDevice;
DX11::sptrDevContext DX11::GraphicExample::mDevContext;
int DX11::GraphicExample::mDisplayTexW;
int DX11::GraphicExample::mDisplayTexH;
DX11::sptrTexSRV DX11::GraphicExample::mPicutreSRV;
DX11::MyFont DX11::GraphicExample::mFont;