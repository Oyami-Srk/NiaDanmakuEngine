using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Danmaker {
	struct Vector2 {
		public Vector2(float _x,float _y) {
			X = _x;
			Y = _y;
		}

		public static Vector2 operator+(Vector2 a, Vector2 b)=> new Vector2(a.X + b.X, a.Y + b.Y);

		public static Vector2 operator-(Vector2 a, Vector2 b)=> new Vector2(a.X - b.X, a.Y - b.Y);

		public static bool operator==(Vector2 a, Vector2 b)=> (a.X == b.X && a.Y == b.Y);

		public static bool operator!=(Vector2 a, Vector2 b)=> (a.X != b.X || a.Y != b.Y);

		public Vector2 Rotate(float _ang) => new Vector2((float)(X * Math.Cos(_ang * Math.PI / 180) - Y * Math.Sin(_ang * Math.PI / 180)),
			(float)(X * Math.Sin(_ang * Math.PI / 180) + Y * Math.Cos(_ang * Math.PI / 180)));

		public float X, Y;

		public static Vector2 Zero = new Vector2(0, 0);
	}
}
