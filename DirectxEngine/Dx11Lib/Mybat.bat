@echo off

echo -------------------------------
echo ---Include files copy Running.....
echo -------------------------------
echo.

setlocal 

REM -----------------------------------------------------------

set "Outdir=.\bin\x64\"
set "foldername=include"
set "DXProjectdir=..\Dx11Project\"
set "Graphic=Graphic"
set "Utility=Utility"
set "DXTKDir=..\common\DirectXTK\include"

REM -----------------------------------------------------------
REM Graphic Folders Names
REM -----------------------------------------------------------

set "FolderGraphic=%Graphic%\"
set "Folder3D=%Graphic%\3D\"
set "FolderFont=%Graphic%\Font\"
set "FolderGUI=%Graphic%\GUI\"
set "FolderTools=%Graphic%\Tools\"
set "FolderToolsTypedef=%Graphic%\Tools\Typedefs\"

echo -------------------------------
echo ---Remove Out dir.....
echo -------------------------------
echo.
rmdir /q /s "%Outdir%\%folderName%"

echo -------------------------------
echo ---Make Out dir.....
echo -------------------------------
echo.
mkdir %Outdir%\%folderName%
mkdir %Outdir%\%folderName%\%FolderGraphic%
mkdir %Outdir%\%folderName%\%Folder3D%
mkdir %Outdir%\%folderName%\%FolderFont%
mkdir %Outdir%\%folderName%\%FolderGUI%
mkdir %Outdir%\%folderName%\%FolderTools%
mkdir %Outdir%\%folderName%\%FolderToolsTypedef%
mkdir %Outdir%\%folderName%\%Utility%

REM -----------------------------------------------------------Graphic
echo -------------------------------
echo ---Copy Graphic.....
echo -------------------------------
echo.

echo %FolderGraphic%
echo.
copy "%DXProjectdir%\%FolderGraphic%\GraphicCommon.h" "%Outdir%\%folderName%\%FolderGraphic%"
copy "%DXProjectdir%\%FolderGraphic%\GraphicTools.h" "%Outdir%\%folderName%\%FolderGraphic%"
copy "%DXProjectdir%\%FolderGraphic%\GraphicExample.h" "%Outdir%\%folderName%\%FolderGraphic%"

echo %Folder3D%
echo.
copy "%DXProjectdir%\%Folder3D%\Camera.h" "%Outdir%\%folderName%\%Folder3D%"
copy "%DXProjectdir%\%Folder3D%\MySTL.h" "%Outdir%\%folderName%\%Folder3D%"
copy "%DXProjectdir%\%Folder3D%\Pick.h" "%Outdir%\%folderName%\%Folder3D%"
copy "%DXProjectdir%\%Folder3D%\STLReader.h" "%Outdir%\%folderName%\%Folder3D%"

echo %FolderFont%
echo.
copy "%DXProjectdir%\%FolderFont%\MyFont.h" "%Outdir%\%folderName%\%FolderFont%"

echo %FolderGUI%
echo.
copy "%DXProjectdir%\%FolderGUI%\GUIButton.h" "%Outdir%\%folderName%\%FolderGUI%" 
copy "%DXProjectdir%\%FolderGUI%\GUICheckBox.h" "%Outdir%\%folderName%\%FolderGUI%" 
copy "%DXProjectdir%\%FolderGUI%\GUIComBox.h" "%Outdir%\%folderName%\%FolderGUI%" 
copy "%DXProjectdir%\%FolderGUI%\GUIListBox.h" "%Outdir%\%folderName%\%FolderGUI%" 
copy "%DXProjectdir%\%FolderGUI%\GUIRadio.h" "%Outdir%\%folderName%\%FolderGUI%" 
copy "%DXProjectdir%\%FolderGUI%\GUIScrollBar.h" "%Outdir%\%folderName%\%FolderGUI%" 
copy "%DXProjectdir%\%FolderGUI%\GUIStatic.h" "%Outdir%\%folderName%\%FolderGUI%" 
copy "%DXProjectdir%\%FolderGUI%\MYGUI.h" "%Outdir%\%folderName%\%FolderGUI%" 
copy "%DXProjectdir%\%FolderGUI%\SettingGUI.h" "%Outdir%\%folderName%\%FolderGUI%" 

echo %FolderTools%
echo.
copy "%DXProjectdir%\%FolderTools%\AdapterTool.h" "%Outdir%\%folderName%\%FolderTools%" 
copy "%DXProjectdir%\%FolderTools%\BlendTool.h" "%Outdir%\%folderName%\%FolderTools%" 
copy "%DXProjectdir%\%FolderTools%\BufferTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\ConstantBufTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\DepthStencilTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\DrawTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\DXDeviceTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\DXWIndowTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\MeshTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\RasterizerTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\RenderTargetViewTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\RenderTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\SamplerTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\ShaderTool.h" "%Outdir%\%folderName%\%FolderTools%"
copy "%DXProjectdir%\%FolderTools%\TextureTool.h" "%Outdir%\%folderName%\%FolderTools%"

echo %FolderToolsTypedef%
echo.
copy "%DXProjectdir%\%FolderToolsTypedef%\ConstantBufferType.h" "%Outdir%\%folderName%\%FolderToolsTypedef%"
copy "%DXProjectdir%\%FolderToolsTypedef%\LayoutStruct.h" "%Outdir%\%folderName%\%FolderToolsTypedef%"
copy "%DXProjectdir%\%FolderToolsTypedef%\MyColor.h" "%Outdir%\%folderName%\%FolderToolsTypedef%"
copy "%DXProjectdir%\%FolderToolsTypedef%\VertexType.h" "%Outdir%\%folderName%\%FolderToolsTypedef%"


REM ----------------------------------------------------------- Utility
echo -------------------------------
echo ---Copy Utility.....
echo -------------------------------
echo.
copy "%DXProjectdir%\%Utility%\utility.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\ErrorLogger.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\FileSystem.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\MyTimer.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\MyTypes.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\SmartPointer.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\StringConverter.h" "%Outdir%\%folderName%\%Utility%"

copy "%DXProjectdir%\%Utility%\KeyboardClass.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\KeyboardEvent.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\MouseClass.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\MouseEvent.h" "%Outdir%\%folderName%\%Utility%"
copy "%DXProjectdir%\%Utility%\MouseKeyboard.h" "%Outdir%\%folderName%\%Utility%"

REM ----------------------------------------------------------- DirectXTK
echo -------------------------------
echo ---Copy DirectXTK.....
echo -------------------------------
echo.
copy "%DXTKDir%\WICTextureLoader.h" "%Outdir%\%folderName%"