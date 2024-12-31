using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Drawing;

namespace FontTool
{
    public class cFontRect
    {
        public int x;
        public int y;
        public int width;
        public int height;
        public cFontRect(){}
        public cFontRect(int _x, int _y, int _width, int _height)
        {
            x = _x;
            y = _y;
            width = _width;
            height = _height;
        }
        public Point getTopLeft() { return new Point(x, y); }
        public Point getTopRight() { return new Point(x + width, y); }
        public Point getBottomLeft() { return new Point(x, y + height); }
        public Point getBottomRight() { return new Point(x + width, y + height); }
        public Point[] getDrawRect()
        {
            return new Point[] {
                                getTopLeft(),
                                getTopRight(),
                                getBottomRight(),
                                getBottomLeft(),
                                getTopLeft(),
                            };
        }
    }
}
