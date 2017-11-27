using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace Mousemove
{
    [Serializable]
    public class Drawing
    {
        public Drawing()
        {
            curves = new List<Curve>();
        }

        List<Curve> curves;

        public List<Curve> Curves
        {
            get { return curves; }
            set { curves = value; }
        }

    }

    [Serializable]
    public class Curve
    {
        List<Point> coordinates;
        TimeSpan _duration;
        TimeSpan _pause;

        Color col;
        float _width;

        #region Properties

        public List<Point> Coordinates
        {
            get { return coordinates; }
            set { coordinates = value; }
        }

        public TimeSpan Duration
        {
            get { return _duration; }
            set { _duration = value; }
        }

        public TimeSpan Pause
        {
            get { return _pause; }
            set { _pause = value; }
        }

        public float Width
        {
            get { return _width; }
            set { _width = value; }
        }

        public Color Color
        {
            get { return col; }
            set { col = value; }
        } 
	    #endregion

        public Curve()
        {
            coordinates = new List<Point>();
            _pause = new TimeSpan(0);
        }

        public Curve(TimeSpan dur,TimeSpan pause,Color color,float width):this()
        {
            _duration = dur;
            _pause = pause;

            col = color;
            _width = width;
        }

    }
}