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

		public Form1() {
			InitializeComponent();
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

		void Graph() {
			g.Clear(Color.Black);
		}

		void GameLoop(double ElapsedTime) {
			Graph();
			counter++;
		}

		int counter = 0;
	}

	public class BaseBallet {
		public delegate double fx(double x);
		fx f;
		BaseBallet(fx _f) {
			f = _f;
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
