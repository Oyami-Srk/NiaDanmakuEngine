using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Danmaker {

	public partial class Form1 : Form {
		Looper timeController;
		Graphics g;
		Graphics surfg;
		Bitmap surface;

		public Form1() {
			InitializeComponent();
			surface = new Bitmap(MainBox.Size.Width, MainBox.Size.Height);
			surfg = Graphics.FromImage(surface);
			Init();
			this.DoubleBuffered = true;
			Timer timer = new Timer();
			timer.Tick += Timer_Counter;
			timer.Interval = 1000;
			timer.Enabled = true;
			timeController = new Looper(GameLoop);
			g = MainBox.CreateGraphics();
		}

		private void Timer_Counter(object sender, EventArgs e) {
			this.Text = "FPS: " + counter.ToString();
			counter = 0;
		}

		List<BaseBallet> bb = new List<BaseBallet>();

		void Init() {
			bb.Add(new BaseBallet(x => (float)Math.Pow(x,2), new Point(225, 225), 0.5f, -5f));
		}

		void DrawAxis(Graphics g, Point center) {
			g.DrawLine(Pens.Aqua, MainBox.Width / 2, 0, MainBox.Width / 2, MainBox.Height);
			g.DrawLine(Pens.Aqua, 0, MainBox.Height / 2, MainBox.Width, MainBox.Height / 2);
		} 

		void Graph() {
			surfg.Clear(Color.Black);
			DrawAxis(surfg, new Point(225, 225));
			foreach (var i in bb)
				i.UpDraw(surfg);

			g.DrawImage(surface, 0, 0);
			//6g.FillEllipse(Brushes.White, 0, 0, 10, 10);
		}

		void GameLoop(double ElapsedTime) {
			Graph();
			counter++;
		}

		int counter = 0;
	}

	public class BaseBallet {
		fx f;
		float inc = 0.0f;
		float x = 0.0f;
		float r = 2.0f;
		Point center;
		Brush br = Brushes.White;
		public delegate float fx(float x);
		public BaseBallet(fx _f, Point _center, float _inc = 1.0f, float _x = 0.0f, float _r = 5.0f) {
			f = _f;
			inc = _inc;
			center = _center;
			x = _x;
			r = _r;
		}

		public void SetBrush(Brush _br) {
			br = _br;
		}

		public void UpDraw(Graphics g) {
			g.TranslateTransform(center.X, center.Y);
			g.FillEllipse(br, x - r, -(f(x) - r), 2 * r, 2 * r);
			x += inc;
			g.ResetTransform();
		}
	}

	public class PreciseTimer {
		[System.Security.SuppressUnmanagedCodeSecurity]
		[DllImport("kernel32")]
		private static extern bool QueryPerformanceFrequency(ref long PerformanceFrequency);
		[System.Security.SuppressUnmanagedCodeSecurity]
		[DllImport("kernel32")]
		private static extern bool QueryPerformanceCounter(ref long PerformanceCounter);

		long _tickPerSecond = 0;
		long _previousElapsedTime = 0;

		public PreciseTimer() {
			QueryPerformanceFrequency(ref _tickPerSecond);
			GetElapsedTime();
		}
		public double GetElapsedTime() {
			long Time = 0;
			QueryPerformanceCounter(ref Time);
			double ElapsedTime = (double)(Time - _previousElapsedTime) / (double)_tickPerSecond;
			return ElapsedTime;
		}

		public void Reset() {
			long Time = 0;
			QueryPerformanceCounter(ref Time);
			double ElapsedTime = (double)(Time - _previousElapsedTime) / (double)_tickPerSecond;
			_previousElapsedTime = Time;
		}
	}

	public class Looper {
		[System.Security.SuppressUnmanagedCodeSecurity]
		[DllImport("User32.dll", CharSet = CharSet.Auto)]
		public static extern bool PeekMessage(
	  out Message Msg,
	  IntPtr hWnd,
	  uint messageFilterMin,
	  uint messageFilterMax,
	  uint flags);

		PreciseTimer _preciseTimer = new PreciseTimer();
		public delegate void LoopCallBack(double ElapsedTime);
		LoopCallBack _loopCallBack;
		public Looper(LoopCallBack CallBack) {
			_loopCallBack = CallBack;
			Application.Idle += new EventHandler(OnApplicationEnterIdle);
		}
		private void OnApplicationEnterIdle(object sender, EventArgs e) {
			while (IsAppStillIdle())
				if (_preciseTimer.GetElapsedTime() >= 0.01667) {
					_loopCallBack(_preciseTimer.GetElapsedTime());
					_preciseTimer.Reset();
				}
		}
		private bool IsAppStillIdle() {
			Message Msg;
			return !PeekMessage(out Msg, IntPtr.Zero, 0, 0, 0);
		}
	}
}
