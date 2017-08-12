﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Uploader
{
	public class JChar
	{
		public static JChar I = new JChar();

		private JChar()
		{
			this.InitCharSet();
		}

		/// <summary>
		/// CP932で表示可能な2バイト文字か判定する。
		/// </summary>
		/// <param name="chr">判定する文字</param>
		/// <returns>CP932で表示可能な2バイト文字であれば true, それ以外は false</returns>
		public bool IsJChar(char chr)
		{
			return _chrSet.Contains(chr);
		}

		private HashSet<char> _chrSet;

		private void InitCharSet()
		{
			_chrSet = new HashSet<char>();

			foreach (char chr in Encoding.GetEncoding(932).GetString(this.GetBytes()))
			{
				_chrSet.Add(chr);
			}
		}

		private List<byte> _bytes;

		private byte[] GetBytes()
		{
			_bytes = new List<byte>();
			this.Add();
			byte[] bytes = _bytes.ToArray();
			_bytes = null;
			return bytes;
		}

		private void Add(UInt16 chr)
		{
			_bytes.Add((byte)(chr >> 8));
			_bytes.Add((byte)chr);
		}

		private void Add(UInt16 bgn, UInt16 end)
		{
			for (UInt16 chr = bgn; chr <= end; chr++)
			{
				this.Add(chr);
			}
		}

		/// <summary>
		/// generated by C:/Factory/Labo/GenData/IsJChar.c
		/// </summary>
		private void Add()
		{
			this.Add(0x8140, 0x817e);
			this.Add(0x8180, 0x81ac);
			this.Add(0x81b8, 0x81bf);
			this.Add(0x81c8, 0x81ce);
			this.Add(0x81da, 0x81e8);
			this.Add(0x81f0, 0x81f7);
			this.Add(0x81fc, 0x81fc);
			this.Add(0x824f, 0x8258);
			this.Add(0x8260, 0x8279);
			this.Add(0x8281, 0x829a);
			this.Add(0x829f, 0x82f1);
			this.Add(0x8340, 0x837e);
			this.Add(0x8380, 0x8396);
			this.Add(0x839f, 0x83b6);
			this.Add(0x83bf, 0x83d6);
			this.Add(0x8440, 0x8460);
			this.Add(0x8470, 0x847e);
			this.Add(0x8480, 0x8491);
			this.Add(0x849f, 0x84be);
			this.Add(0x8740, 0x875d);
			this.Add(0x875f, 0x8775);
			this.Add(0x877e, 0x877e);
			this.Add(0x8780, 0x879c);
			this.Add(0x889f, 0x88fc);
			this.Add(0x8940, 0x897e);
			this.Add(0x8980, 0x89fc);
			this.Add(0x8a40, 0x8a7e);
			this.Add(0x8a80, 0x8afc);
			this.Add(0x8b40, 0x8b7e);
			this.Add(0x8b80, 0x8bfc);
			this.Add(0x8c40, 0x8c7e);
			this.Add(0x8c80, 0x8cfc);
			this.Add(0x8d40, 0x8d7e);
			this.Add(0x8d80, 0x8dfc);
			this.Add(0x8e40, 0x8e7e);
			this.Add(0x8e80, 0x8efc);
			this.Add(0x8f40, 0x8f7e);
			this.Add(0x8f80, 0x8ffc);
			this.Add(0x9040, 0x907e);
			this.Add(0x9080, 0x90fc);
			this.Add(0x9140, 0x917e);
			this.Add(0x9180, 0x91fc);
			this.Add(0x9240, 0x927e);
			this.Add(0x9280, 0x92fc);
			this.Add(0x9340, 0x937e);
			this.Add(0x9380, 0x93fc);
			this.Add(0x9440, 0x947e);
			this.Add(0x9480, 0x94fc);
			this.Add(0x9540, 0x957e);
			this.Add(0x9580, 0x95fc);
			this.Add(0x9640, 0x967e);
			this.Add(0x9680, 0x96fc);
			this.Add(0x9740, 0x977e);
			this.Add(0x9780, 0x97fc);
			this.Add(0x9840, 0x9872);
			this.Add(0x989f, 0x98fc);
			this.Add(0x9940, 0x997e);
			this.Add(0x9980, 0x99fc);
			this.Add(0x9a40, 0x9a7e);
			this.Add(0x9a80, 0x9afc);
			this.Add(0x9b40, 0x9b7e);
			this.Add(0x9b80, 0x9bfc);
			this.Add(0x9c40, 0x9c7e);
			this.Add(0x9c80, 0x9cfc);
			this.Add(0x9d40, 0x9d7e);
			this.Add(0x9d80, 0x9dfc);
			this.Add(0x9e40, 0x9e7e);
			this.Add(0x9e80, 0x9efc);
			this.Add(0x9f40, 0x9f7e);
			this.Add(0x9f80, 0x9ffc);
			this.Add(0xe040, 0xe07e);
			this.Add(0xe080, 0xe0fc);
			this.Add(0xe140, 0xe17e);
			this.Add(0xe180, 0xe1fc);
			this.Add(0xe240, 0xe27e);
			this.Add(0xe280, 0xe2fc);
			this.Add(0xe340, 0xe37e);
			this.Add(0xe380, 0xe3fc);
			this.Add(0xe440, 0xe47e);
			this.Add(0xe480, 0xe4fc);
			this.Add(0xe540, 0xe57e);
			this.Add(0xe580, 0xe5fc);
			this.Add(0xe640, 0xe67e);
			this.Add(0xe680, 0xe6fc);
			this.Add(0xe740, 0xe77e);
			this.Add(0xe780, 0xe7fc);
			this.Add(0xe840, 0xe87e);
			this.Add(0xe880, 0xe8fc);
			this.Add(0xe940, 0xe97e);
			this.Add(0xe980, 0xe9fc);
			this.Add(0xea40, 0xea7e);
			this.Add(0xea80, 0xeaa4);
			this.Add(0xed40, 0xed7e);
			this.Add(0xed80, 0xedfc);
			this.Add(0xee40, 0xee7e);
			this.Add(0xee80, 0xeeec);
			this.Add(0xeeef, 0xeefc);
			this.Add(0xfa40, 0xfa7e);
			this.Add(0xfa80, 0xfafc);
			this.Add(0xfb40, 0xfb7e);
			this.Add(0xfb80, 0xfbfc);
			this.Add(0xfc40, 0xfc4b);
		}
	}
}
