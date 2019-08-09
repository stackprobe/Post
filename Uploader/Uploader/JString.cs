using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Uploader
{
	public static class JString
	{
		/// <summary>
		/// CR, CR-LF, LF -> LF
		/// </summary>
		/// <param name="str"></param>
		/// <returns></returns>
		public static string ToLfOnly(string str)
		{
			str = str.Replace("\r\n", "\r");
			str = str.Replace("\r", "\n");

			return str;
		}

		public static bool IsJString(string str, bool okJpn, bool okRet, bool okTab, bool okSpc, int minlen = 0, int maxlen = int.MaxValue)
		{
			return str == ToJString(str, okJpn, okRet, okTab, okSpc, minlen, maxlen);
		}

		private const char DEF_CHR = '？';

		public static string ToJString(string str, bool okJpn, bool okRet, bool okTab, bool okSpc, int minlen = 0, int maxlen = int.MaxValue)
		{
			StringBuilder buff = new StringBuilder();

			str = ToLfOnly(str);

			foreach (char chr in str)
			{
				if (
					(okJpn && JChar.I.IsJChar(chr)) ||
					(okRet && chr == '\n') ||
					(okTab && chr == '\t') ||
					(okSpc && chr == ' ') ||
					IsPunctDigitAlpha(chr) ||
					IsKana(chr)
					)
					buff.Append(chr);
				else
					buff.Append(DEF_CHR);
			}
			while (buff.Length < minlen)
				buff.Append(DEF_CHR);

			str = buff.ToString();

			if (maxlen < str.Length)
				str = str.Substring(0, maxlen);

			return str;
		}

		public static bool IsPunctDigitAlpha(char chr)
		{
			return '\x0021' <= chr && chr <= '\x007e';
		}

		public static bool IsKana(char chr)
		{
			return '\x00a1' <= chr && chr <= '\x00df';
		}
	}
}
