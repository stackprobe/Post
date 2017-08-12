using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Uploader
{
	public class Tools
	{
		public static readonly Encoding ENCODING_SJIS = Encoding.GetEncoding(932);

		public static long RangeLong(long value, long minval, long maxval)
		{
			value = Math.Max(value, minval);
			value = Math.Min(value, maxval);

			return value;
		}

		public static long ParseLong(string line, long minval, long maxval, long defval)
		{
			long value;

			try
			{
				value = long.Parse(line);
			}
			catch
			{
				value = defval;
			}
			return RangeLong(value, minval, maxval);
		}

		public static string Unctrl(string str)
		{
			StringBuilder buff = new StringBuilder();

			foreach (char chr in str)
				if (' ' < chr && chr != '　')
					buff.Append(chr);

			return buff.ToString();
		}

		public static string ExtsFltr(string exts)
		{
			try
			{
				exts = Unctrl(exts);
				exts = "." + exts + ".";
				for (int c = 0; c < 20; c++) exts = exts.Replace("..", ".");
				exts = exts.Substring(1, exts.Length - 2);
				return exts;
			}
			catch
			{ }

			return "";
		}
	}

	public class EventSet
	{
		[DllImport("kernel32.dll")]
		private static extern IntPtr CreateEvent(IntPtr lpEventAttributes, bool bManualReset, bool bInitialState, string lpName);

		[DllImport("kernel32.dll")]
		private static extern bool SetEvent(IntPtr hEvent);

		[DllImport("kernel32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool CloseHandle(IntPtr hObject);

		public static void Perform(string eventName)
		{
			try
			{
				IntPtr hdl = CreateEvent((IntPtr)0, false, false, eventName);

				if (hdl == (IntPtr)0)
					throw new Exception();

				SetEvent(hdl);
				CloseHandle(hdl);
			}
			catch
			{ }
		}
	}
}
