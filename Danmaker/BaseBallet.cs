using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Danmaker {
	struct BalletDescriber {
		public Vector2 Speed;
		public Vector2 SpeedInc;
		public float RotationInc;
		public int FramesDelay;
	};

	//static Vector2 Vector2Zero = new Vector2(0, 0);

	class BaseBallet {
		public BaseBallet(List<BalletDescriber> _anim, Vector2 _Position) {
			Anim = new List<BalletDescriber>();
			Position = _Position;
			Anim = _anim;
		}

		public BaseBallet(Vector2 _Position, Vector2 Speed, Vector2 SpeedInc, float RotationInc = 0.0f, int _Fdelay = 0) {
			Anim = new List<BalletDescriber>();
			Position = _Position;
			BalletDescriber B;
			B.FramesDelay = _Fdelay;
			B.RotationInc = RotationInc;
			B.SpeedInc = SpeedInc;
			B.Speed = Speed;
			Anim.Add(B);
		}

		public void PushMov(Vector2 Speed, Vector2 SpeedInc, float RotationInc, int _Fdelay) {
			BalletDescriber B;
			B.FramesDelay = _Fdelay;
			B.RotationInc = RotationInc;
			B.SpeedInc = SpeedInc;
			B.Speed = Speed;
			Anim.Add(B);
		}

		public Vector2 GetPosition() {
			if (Anim.Count <= 0)
				isDestoryed = true;
			else if (Anim.Count == 1)
				_change_Position_by_AnimId(0);
			else {
				int TotalDelay = 0;
				int i = 0;
				bool set = false;
				foreach(var v in Anim) {
					TotalDelay += v.FramesDelay;
					if(v.FramesDelay == -1 || nCount <= TotalDelay) {
						_change_Position_by_AnimId(i);
						set = true;
						break;
					}
					i++;
				}
				if (!set)
					isDestoryed = true;
			}
			if (isDestoryed)
				Position = new Vector2(0, 0);
			nCount++;
			return Position;
		}

		private void _change_Position_by_AnimId(int id) {
			Position += (Anim[id].Speed);
			/*There is a question in sentences below: Rotate the speed first or increase the speed first*/
			BalletDescriber tmp;
			tmp = Anim[id];
			tmp.Speed = tmp.Speed + tmp.SpeedInc;
			tmp.Speed = tmp.Speed.Rotate(tmp.RotationInc);
			Anim[id] = tmp;
			//Anim[id].Speed += (Anim[id].SpeedInc = Anim[id].SpeedInc.Rotate(Anim[id].RotationInc));
		}

		public bool CheckOutside(float Width, float Height, float R) {
			if (Position.X > (Width + R) || Position.Y > (Height + R)) {
				isDestoryed = true;
				return true;
			}
			return isDestoryed;
		}

		public Vector2 Position;
		public List<BalletDescriber> Anim;
		public int nCount = 0;
		public bool isDestoryed = false;
	}
}
