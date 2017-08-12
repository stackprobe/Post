using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;

namespace Uploader
{
	public class HTTProc
	{
		private Process Proc;

		public void 共通()
		{
			if (this.Proc != null)
			{
				if (this.Proc.HasExited)
				{
					this.Proc.Close();
					this.Proc = null;
				}
			}
		}

		public bool Is開始()
		{
			this.共通();
			return this.Proc != null;
		}

		public void 開始()
		{
			this.共通();

			if (this.Proc == null)
			{
				try
				{
					ProcessStartInfo psi = new ProcessStartInfo();

					psi.FileName = "HTT.exe";
					psi.Arguments = "/U " + Gnd.I.HTT_APP_UUID + " /P " + Gnd.I.GetPortNo() + " /S Service.dat";
					psi.CreateNoWindow = true;
					psi.UseShellExecute = false;

					if (Gnd.I.ShowConsoleMode == Gnd.ShowConsoleMode_e.SHOW_MIN)
					{
						psi.CreateNoWindow = false;
						psi.UseShellExecute = true; // これをしないと最小化されない！
						psi.WindowStyle = ProcessWindowStyle.Minimized;
					}
					else if (Gnd.I.ShowConsoleMode == Gnd.ShowConsoleMode_e.SHOW_NORMAL)
					{
						psi.CreateNoWindow = false;
					}
					this.Proc = Process.Start(psi);
				}
				catch
				{ }
			}
		}

		public void 停止()
		{
			this.共通();

			if (this.Proc != null)
			{
				this.Do停止();
			}
		}

		private void Do停止()
		{
			using (BusyWin f = new BusyWin())
			{
				f.DoStart(new Thread(this.Do停止Th));
				f.ShowDialog();
			}
		}

		private void Do停止Th()
		{
			do
			{
				Do停止信号();
			}
			while (this.Proc.WaitForExit(3000) == false); // ? 終わらない

			this.Proc.Close();
			this.Proc = null;
		}

		public static void Do停止信号()
		{
			try
			{
#if false
				// イベント名は大文字・小文字区別する。
				// HTT.exe では APP_UUID を大文字にしている！

				EventSet.Perform("cerulean.charlotte HTT after-school tea time server termination " + Gnd.I.HTT_APP_UUID.ToUpper());
				//EventSet.Perform("cerulean.charlotte HTT after-school tea time server termination"); // OLD
#else
				ProcessStartInfo psi = new ProcessStartInfo();

				psi.FileName = "HTT.exe";
				psi.Arguments = "/U " + Gnd.I.HTT_APP_UUID + " /T";
				psi.CreateNoWindow = true;
				psi.UseShellExecute = false;

				Process.Start(psi).WaitForExit();
#endif
			}
			catch
			{ }
		}
	}
}
