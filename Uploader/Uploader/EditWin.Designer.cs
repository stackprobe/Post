namespace Uploader
{
	partial class EditWin
	{
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナーで生成されたコード

		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EditWin));
			this.PortNo = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.UploadDir = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.リセットBtn = new System.Windows.Forms.Button();
			this.UploadDiskFreeMin = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.UploadedFileNumMax = new System.Windows.Forms.TextBox();
			this.label7 = new System.Windows.Forms.Label();
			this.DateLangJ = new System.Windows.Forms.CheckBox();
			this.label8 = new System.Windows.Forms.Label();
			this.label9 = new System.Windows.Forms.Label();
			this.UploadDirSizeMax = new System.Windows.Forms.TextBox();
			this.ShowDeleteButtonFlag = new System.Windows.Forms.CheckBox();
			this.ToolTips = new System.Windows.Forms.ToolTip(this.components);
			this.ImageExts = new System.Windows.Forms.TextBox();
			this.ShowedImageTotalSizeMax = new System.Windows.Forms.TextBox();
			this.UploadDirSizeMaxデフォルトBtn = new System.Windows.Forms.Button();
			this.UploadDiskFreeMinデフォルトBtn = new System.Windows.Forms.Button();
			this.Password = new System.Windows.Forms.TextBox();
			this.UploadedFileNumMaxデフォルトBtn = new System.Windows.Forms.Button();
			this.デフォルトBtn = new System.Windows.Forms.Button();
			this.ShowedImageTotalSizeMaxデフォルトBtn = new System.Windows.Forms.Button();
			this.PortNoデフォルトBtn = new System.Windows.Forms.Button();
			this.UploadDirデフォルトBtn = new System.Windows.Forms.Button();
			this.MovieMusicEmbedBtn = new System.Windows.Forms.Button();
			this.画像の表示Grp = new System.Windows.Forms.GroupBox();
			this.画像ラベル2 = new System.Windows.Forms.Label();
			this.画像ラベル1_1 = new System.Windows.Forms.Label();
			this.ShowImageFlag = new System.Windows.Forms.CheckBox();
			this.画像ラベル1 = new System.Windows.Forms.Label();
			this.PasswordEnabled = new System.Windows.Forms.CheckBox();
			this.NoOverwriteFlag = new System.Windows.Forms.CheckBox();
			this.ShowDownloadLinkFlag = new System.Windows.Forms.CheckBox();
			this.SortOrder = new System.Windows.Forms.ComboBox();
			this.label3 = new System.Windows.Forms.Label();
			this.NoUpFavicon = new System.Windows.Forms.CheckBox();
			this.画像の表示Grp.SuspendLayout();
			this.SuspendLayout();
			// 
			// PortNo
			// 
			this.PortNo.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.PortNo.Location = new System.Drawing.Point(253, 24);
			this.PortNo.MaxLength = 5;
			this.PortNo.Name = "PortNo";
			this.PortNo.Size = new System.Drawing.Size(72, 31);
			this.PortNo.TabIndex = 1;
			this.PortNo.Text = "65000";
			this.PortNo.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.ToolTips.SetToolTip(this.PortNo, "1 ～ 65535");
			this.PortNo.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.PortNo_KeyPress);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label1.Location = new System.Drawing.Point(23, 27);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(90, 24);
			this.label1.TabIndex = 0;
			this.label1.Text = "ポート番号";
			// 
			// UploadDir
			// 
			this.UploadDir.Cursor = System.Windows.Forms.Cursors.Hand;
			this.UploadDir.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.UploadDir.Location = new System.Drawing.Point(253, 171);
			this.UploadDir.Name = "UploadDir";
			this.UploadDir.ReadOnly = true;
			this.UploadDir.Size = new System.Drawing.Size(393, 31);
			this.UploadDir.TabIndex = 15;
			this.UploadDir.Text = "(PATH)";
			this.ToolTips.SetToolTip(this.UploadDir, "クリックしてフォルダを選択して下さい。");
			this.UploadDir.Click += new System.EventHandler(this.UploadDir_Click);
			this.UploadDir.TextChanged += new System.EventHandler(this.UploadDir_TextChanged);
			this.UploadDir.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UploadDir_KeyPress);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label2.Location = new System.Drawing.Point(23, 174);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(186, 24);
			this.label2.TabIndex = 14;
			this.label2.Text = "アップロード先フォルダ";
			// 
			// リセットBtn
			// 
			this.リセットBtn.Font = new System.Drawing.Font("メイリオ", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.リセットBtn.Location = new System.Drawing.Point(610, 484);
			this.リセットBtn.Name = "リセットBtn";
			this.リセットBtn.Size = new System.Drawing.Size(128, 54);
			this.リセットBtn.TabIndex = 29;
			this.リセットBtn.Text = "リセット";
			this.ToolTips.SetToolTip(this.リセットBtn, "このダイアログを開いた時の状態に戻します。");
			this.リセットBtn.UseVisualStyleBackColor = true;
			this.リセットBtn.Click += new System.EventHandler(this.リセットBtn_Click);
			// 
			// UploadDiskFreeMin
			// 
			this.UploadDiskFreeMin.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.UploadDiskFreeMin.Location = new System.Drawing.Point(253, 97);
			this.UploadDiskFreeMin.MaxLength = 19;
			this.UploadDiskFreeMin.Name = "UploadDiskFreeMin";
			this.UploadDiskFreeMin.Size = new System.Drawing.Size(211, 31);
			this.UploadDiskFreeMin.TabIndex = 8;
			this.UploadDiskFreeMin.Text = "1234567890123456789";
			this.UploadDiskFreeMin.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.ToolTips.SetToolTip(this.UploadDiskFreeMin, "0 ～ 9223372036854775807");
			this.UploadDiskFreeMin.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UploadDiskFreeMin_KeyPress);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label5.Location = new System.Drawing.Point(23, 100);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(218, 24);
			this.label5.TabIndex = 7;
			this.label5.Text = "確保するディスクの空き領域";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label6.Location = new System.Drawing.Point(470, 100);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(58, 24);
			this.label6.TabIndex = 9;
			this.label6.Text = "バイト";
			// 
			// UploadedFileNumMax
			// 
			this.UploadedFileNumMax.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.UploadedFileNumMax.Location = new System.Drawing.Point(253, 134);
			this.UploadedFileNumMax.MaxLength = 10;
			this.UploadedFileNumMax.Name = "UploadedFileNumMax";
			this.UploadedFileNumMax.Size = new System.Drawing.Size(121, 31);
			this.UploadedFileNumMax.TabIndex = 12;
			this.UploadedFileNumMax.Text = "1234567890";
			this.UploadedFileNumMax.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.ToolTips.SetToolTip(this.UploadedFileNumMax, "1 ～ 2147483647");
			this.UploadedFileNumMax.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UploadedFileNumMax_KeyPress);
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label7.Location = new System.Drawing.Point(23, 137);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(138, 24);
			this.label7.TabIndex = 11;
			this.label7.Text = "ファイル数の上限";
			// 
			// DateLangJ
			// 
			this.DateLangJ.AutoSize = true;
			this.DateLangJ.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.DateLangJ.Location = new System.Drawing.Point(253, 366);
			this.DateLangJ.Name = "DateLangJ";
			this.DateLangJ.Size = new System.Drawing.Size(192, 28);
			this.DateLangJ.TabIndex = 22;
			this.DateLangJ.Text = "日付をYMDで表記する";
			this.DateLangJ.UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label8.Location = new System.Drawing.Point(470, 64);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(58, 24);
			this.label8.TabIndex = 5;
			this.label8.Text = "バイト";
			// 
			// label9
			// 
			this.label9.AutoSize = true;
			this.label9.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label9.Location = new System.Drawing.Point(23, 64);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(202, 24);
			this.label9.TabIndex = 3;
			this.label9.Text = "ファイル合計サイズの上限";
			// 
			// UploadDirSizeMax
			// 
			this.UploadDirSizeMax.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.UploadDirSizeMax.Location = new System.Drawing.Point(253, 61);
			this.UploadDirSizeMax.MaxLength = 19;
			this.UploadDirSizeMax.Name = "UploadDirSizeMax";
			this.UploadDirSizeMax.Size = new System.Drawing.Size(211, 31);
			this.UploadDirSizeMax.TabIndex = 4;
			this.UploadDirSizeMax.Text = "1234567890123456789";
			this.UploadDirSizeMax.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.ToolTips.SetToolTip(this.UploadDirSizeMax, "0 ～ 9223372036854775807");
			this.UploadDirSizeMax.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UploadDirSizeMax_KeyPress);
			// 
			// ShowDeleteButtonFlag
			// 
			this.ShowDeleteButtonFlag.AutoSize = true;
			this.ShowDeleteButtonFlag.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.ShowDeleteButtonFlag.Location = new System.Drawing.Point(253, 434);
			this.ShowDeleteButtonFlag.Name = "ShowDeleteButtonFlag";
			this.ShowDeleteButtonFlag.Size = new System.Drawing.Size(189, 28);
			this.ShowDeleteButtonFlag.TabIndex = 24;
			this.ShowDeleteButtonFlag.Text = "削除ボタンを表示する";
			this.ShowDeleteButtonFlag.UseVisualStyleBackColor = true;
			// 
			// ImageExts
			// 
			this.ImageExts.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.ImageExts.Location = new System.Drawing.Point(241, 98);
			this.ImageExts.MaxLength = 1000;
			this.ImageExts.Name = "ImageExts";
			this.ImageExts.Size = new System.Drawing.Size(465, 31);
			this.ImageExts.TabIndex = 6;
			this.ImageExts.Text = "ext.ext.ext";
			this.ToolTips.SetToolTip(this.ImageExts, "拡張子を半角ピリオドで区切って記述して下さい。");
			this.ImageExts.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.ImageExts_KeyPress);
			// 
			// ShowedImageTotalSizeMax
			// 
			this.ShowedImageTotalSizeMax.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.ShowedImageTotalSizeMax.Location = new System.Drawing.Point(241, 61);
			this.ShowedImageTotalSizeMax.MaxLength = 19;
			this.ShowedImageTotalSizeMax.Name = "ShowedImageTotalSizeMax";
			this.ShowedImageTotalSizeMax.Size = new System.Drawing.Size(211, 31);
			this.ShowedImageTotalSizeMax.TabIndex = 2;
			this.ShowedImageTotalSizeMax.Text = "1234567890123456789";
			this.ShowedImageTotalSizeMax.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.ToolTips.SetToolTip(this.ShowedImageTotalSizeMax, "0 ～ 9223372036854775807");
			this.ShowedImageTotalSizeMax.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.ShowedImageTotalSizeMax_KeyPress);
			// 
			// UploadDirSizeMaxデフォルトBtn
			// 
			this.UploadDirSizeMaxデフォルトBtn.Font = new System.Drawing.Font("メイリオ", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.UploadDirSizeMaxデフォルトBtn.Location = new System.Drawing.Point(549, 61);
			this.UploadDirSizeMaxデフォルトBtn.Name = "UploadDirSizeMaxデフォルトBtn";
			this.UploadDirSizeMaxデフォルトBtn.Size = new System.Drawing.Size(97, 31);
			this.UploadDirSizeMaxデフォルトBtn.TabIndex = 6;
			this.UploadDirSizeMaxデフォルトBtn.Text = "デフォルト";
			this.ToolTips.SetToolTip(this.UploadDirSizeMaxデフォルトBtn, "[ファイル合計サイズの上限]をデフォルト値に戻します。");
			this.UploadDirSizeMaxデフォルトBtn.UseVisualStyleBackColor = true;
			this.UploadDirSizeMaxデフォルトBtn.Click += new System.EventHandler(this.UploadDirSizeMaxデフォルトBtn_Click);
			// 
			// UploadDiskFreeMinデフォルトBtn
			// 
			this.UploadDiskFreeMinデフォルトBtn.Font = new System.Drawing.Font("メイリオ", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.UploadDiskFreeMinデフォルトBtn.Location = new System.Drawing.Point(549, 98);
			this.UploadDiskFreeMinデフォルトBtn.Name = "UploadDiskFreeMinデフォルトBtn";
			this.UploadDiskFreeMinデフォルトBtn.Size = new System.Drawing.Size(97, 31);
			this.UploadDiskFreeMinデフォルトBtn.TabIndex = 10;
			this.UploadDiskFreeMinデフォルトBtn.Text = "デフォルト";
			this.ToolTips.SetToolTip(this.UploadDiskFreeMinデフォルトBtn, "[確保するディスクの空き領域]をデフォルト値に戻します。");
			this.UploadDiskFreeMinデフォルトBtn.UseVisualStyleBackColor = true;
			this.UploadDiskFreeMinデフォルトBtn.Click += new System.EventHandler(this.UploadDiskFreeMinデフォルトBtn_Click);
			// 
			// Password
			// 
			this.Password.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.Password.Location = new System.Drawing.Point(27, 400);
			this.Password.MaxLength = 1000;
			this.Password.Name = "Password";
			this.Password.Size = new System.Drawing.Size(189, 31);
			this.Password.TabIndex = 19;
			this.Password.Text = "abc123あいう";
			this.ToolTips.SetToolTip(this.Password, "1文字以上、半角全角・大文字小文字は区別します。");
			this.Password.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Password_KeyPress);
			// 
			// UploadedFileNumMaxデフォルトBtn
			// 
			this.UploadedFileNumMaxデフォルトBtn.Font = new System.Drawing.Font("メイリオ", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.UploadedFileNumMaxデフォルトBtn.Location = new System.Drawing.Point(549, 134);
			this.UploadedFileNumMaxデフォルトBtn.Name = "UploadedFileNumMaxデフォルトBtn";
			this.UploadedFileNumMaxデフォルトBtn.Size = new System.Drawing.Size(97, 31);
			this.UploadedFileNumMaxデフォルトBtn.TabIndex = 13;
			this.UploadedFileNumMaxデフォルトBtn.Text = "デフォルト";
			this.ToolTips.SetToolTip(this.UploadedFileNumMaxデフォルトBtn, "[ファイル数の上限]をデフォルト値に戻します。");
			this.UploadedFileNumMaxデフォルトBtn.UseVisualStyleBackColor = true;
			this.UploadedFileNumMaxデフォルトBtn.Click += new System.EventHandler(this.UploadedFileNumMaxデフォルトBtn_Click);
			// 
			// デフォルトBtn
			// 
			this.デフォルトBtn.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.デフォルトBtn.Location = new System.Drawing.Point(476, 484);
			this.デフォルトBtn.Name = "デフォルトBtn";
			this.デフォルトBtn.Size = new System.Drawing.Size(128, 54);
			this.デフォルトBtn.TabIndex = 28;
			this.デフォルトBtn.Text = "デフォルト";
			this.ToolTips.SetToolTip(this.デフォルトBtn, "全ての項目をデフォルト値に戻します。");
			this.デフォルトBtn.UseVisualStyleBackColor = true;
			this.デフォルトBtn.Click += new System.EventHandler(this.デフォルトBtn_Click);
			// 
			// ShowedImageTotalSizeMaxデフォルトBtn
			// 
			this.ShowedImageTotalSizeMaxデフォルトBtn.Font = new System.Drawing.Font("メイリオ", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.ShowedImageTotalSizeMaxデフォルトBtn.Location = new System.Drawing.Point(609, 61);
			this.ShowedImageTotalSizeMaxデフォルトBtn.Name = "ShowedImageTotalSizeMaxデフォルトBtn";
			this.ShowedImageTotalSizeMaxデフォルトBtn.Size = new System.Drawing.Size(97, 31);
			this.ShowedImageTotalSizeMaxデフォルトBtn.TabIndex = 4;
			this.ShowedImageTotalSizeMaxデフォルトBtn.Text = "デフォルト";
			this.ToolTips.SetToolTip(this.ShowedImageTotalSizeMaxデフォルトBtn, "[画像の表示]をデフォルト値に戻します。");
			this.ShowedImageTotalSizeMaxデフォルトBtn.UseVisualStyleBackColor = true;
			this.ShowedImageTotalSizeMaxデフォルトBtn.Click += new System.EventHandler(this.ShowedImageTotalSizeMaxデフォルトBtn_Click);
			// 
			// PortNoデフォルトBtn
			// 
			this.PortNoデフォルトBtn.Font = new System.Drawing.Font("メイリオ", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.PortNoデフォルトBtn.Location = new System.Drawing.Point(549, 24);
			this.PortNoデフォルトBtn.Name = "PortNoデフォルトBtn";
			this.PortNoデフォルトBtn.Size = new System.Drawing.Size(97, 31);
			this.PortNoデフォルトBtn.TabIndex = 2;
			this.PortNoデフォルトBtn.Text = "デフォルト";
			this.ToolTips.SetToolTip(this.PortNoデフォルトBtn, "[ポート番号]をデフォルト値に戻します。");
			this.PortNoデフォルトBtn.UseVisualStyleBackColor = true;
			this.PortNoデフォルトBtn.Click += new System.EventHandler(this.PortNoデフォルトBtn_Click);
			// 
			// UploadDirデフォルトBtn
			// 
			this.UploadDirデフォルトBtn.Font = new System.Drawing.Font("メイリオ", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.UploadDirデフォルトBtn.Location = new System.Drawing.Point(652, 171);
			this.UploadDirデフォルトBtn.Name = "UploadDirデフォルトBtn";
			this.UploadDirデフォルトBtn.Size = new System.Drawing.Size(97, 31);
			this.UploadDirデフォルトBtn.TabIndex = 16;
			this.UploadDirデフォルトBtn.Text = "デフォルト";
			this.ToolTips.SetToolTip(this.UploadDirデフォルトBtn, "[アップロード先フォルダ]をデフォルト値に戻します。");
			this.UploadDirデフォルトBtn.UseVisualStyleBackColor = true;
			this.UploadDirデフォルトBtn.Click += new System.EventHandler(this.UploadDirデフォルトBtn_Click);
			// 
			// MovieMusicEmbedBtn
			// 
			this.MovieMusicEmbedBtn.Font = new System.Drawing.Font("メイリオ", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.MovieMusicEmbedBtn.Location = new System.Drawing.Point(498, 400);
			this.MovieMusicEmbedBtn.Name = "MovieMusicEmbedBtn";
			this.MovieMusicEmbedBtn.Size = new System.Drawing.Size(240, 31);
			this.MovieMusicEmbedBtn.TabIndex = 27;
			this.MovieMusicEmbedBtn.Text = "動画・音楽ファイルの埋め込み";
			this.ToolTips.SetToolTip(this.MovieMusicEmbedBtn, "[画像の表示]をデフォルト値に戻します。");
			this.MovieMusicEmbedBtn.UseVisualStyleBackColor = true;
			this.MovieMusicEmbedBtn.Click += new System.EventHandler(this.MovieMusicEmbedBtn_Click);
			// 
			// 画像の表示Grp
			// 
			this.画像の表示Grp.Controls.Add(this.ShowedImageTotalSizeMaxデフォルトBtn);
			this.画像の表示Grp.Controls.Add(this.画像ラベル2);
			this.画像の表示Grp.Controls.Add(this.ImageExts);
			this.画像の表示Grp.Controls.Add(this.画像ラベル1_1);
			this.画像の表示Grp.Controls.Add(this.ShowImageFlag);
			this.画像の表示Grp.Controls.Add(this.画像ラベル1);
			this.画像の表示Grp.Controls.Add(this.ShowedImageTotalSizeMax);
			this.画像の表示Grp.Font = new System.Drawing.Font("メイリオ", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.画像の表示Grp.Location = new System.Drawing.Point(12, 208);
			this.画像の表示Grp.Name = "画像の表示Grp";
			this.画像の表示Grp.Size = new System.Drawing.Size(726, 152);
			this.画像の表示Grp.TabIndex = 17;
			this.画像の表示Grp.TabStop = false;
			this.画像の表示Grp.Text = "画像の表示";
			// 
			// 画像ラベル2
			// 
			this.画像ラベル2.AutoSize = true;
			this.画像ラベル2.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.画像ラベル2.Location = new System.Drawing.Point(11, 101);
			this.画像ラベル2.Name = "画像ラベル2";
			this.画像ラベル2.Size = new System.Drawing.Size(170, 24);
			this.画像ラベル2.TabIndex = 5;
			this.画像ラベル2.Text = "画像ファイルの拡張子";
			// 
			// 画像ラベル1_1
			// 
			this.画像ラベル1_1.AutoSize = true;
			this.画像ラベル1_1.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.画像ラベル1_1.Location = new System.Drawing.Point(458, 64);
			this.画像ラベル1_1.Name = "画像ラベル1_1";
			this.画像ラベル1_1.Size = new System.Drawing.Size(58, 24);
			this.画像ラベル1_1.TabIndex = 3;
			this.画像ラベル1_1.Text = "バイト";
			// 
			// ShowImageFlag
			// 
			this.ShowImageFlag.AutoSize = true;
			this.ShowImageFlag.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.ShowImageFlag.Location = new System.Drawing.Point(241, 27);
			this.ShowImageFlag.Name = "ShowImageFlag";
			this.ShowImageFlag.Size = new System.Drawing.Size(141, 28);
			this.ShowImageFlag.TabIndex = 0;
			this.ShowImageFlag.Text = "画像を表示する";
			this.ShowImageFlag.UseVisualStyleBackColor = true;
			this.ShowImageFlag.CheckedChanged += new System.EventHandler(this.ShowImageFlag_CheckedChanged);
			this.ShowImageFlag.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.ShowImageFlag_KeyPress);
			// 
			// 画像ラベル1
			// 
			this.画像ラベル1.AutoSize = true;
			this.画像ラベル1.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.画像ラベル1.Location = new System.Drawing.Point(11, 64);
			this.画像ラベル1.Name = "画像ラベル1";
			this.画像ラベル1.Size = new System.Drawing.Size(184, 24);
			this.画像ラベル1.TabIndex = 1;
			this.画像ラベル1.Text = "画像(累計)サイズの上限";
			// 
			// PasswordEnabled
			// 
			this.PasswordEnabled.AutoSize = true;
			this.PasswordEnabled.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.PasswordEnabled.Location = new System.Drawing.Point(27, 366);
			this.PasswordEnabled.Name = "PasswordEnabled";
			this.PasswordEnabled.Size = new System.Drawing.Size(109, 28);
			this.PasswordEnabled.TabIndex = 18;
			this.PasswordEnabled.Text = "パスワード";
			this.PasswordEnabled.UseVisualStyleBackColor = true;
			this.PasswordEnabled.CheckedChanged += new System.EventHandler(this.PasswordEnabled_CheckedChanged);
			// 
			// NoOverwriteFlag
			// 
			this.NoOverwriteFlag.AutoSize = true;
			this.NoOverwriteFlag.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.NoOverwriteFlag.Location = new System.Drawing.Point(253, 468);
			this.NoOverwriteFlag.Name = "NoOverwriteFlag";
			this.NoOverwriteFlag.Size = new System.Drawing.Size(109, 28);
			this.NoOverwriteFlag.TabIndex = 25;
			this.NoOverwriteFlag.Text = "上書き禁止";
			this.NoOverwriteFlag.UseVisualStyleBackColor = true;
			// 
			// ShowDownloadLinkFlag
			// 
			this.ShowDownloadLinkFlag.AutoSize = true;
			this.ShowDownloadLinkFlag.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.ShowDownloadLinkFlag.Location = new System.Drawing.Point(253, 400);
			this.ShowDownloadLinkFlag.Name = "ShowDownloadLinkFlag";
			this.ShowDownloadLinkFlag.Size = new System.Drawing.Size(233, 28);
			this.ShowDownloadLinkFlag.TabIndex = 23;
			this.ShowDownloadLinkFlag.Text = "downloadリンクを表示する";
			this.ShowDownloadLinkFlag.UseVisualStyleBackColor = true;
			// 
			// SortOrder
			// 
			this.SortOrder.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.SortOrder.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.SortOrder.FormattingEnabled = true;
			this.SortOrder.Items.AddRange(new object[] {
            "新しい→古い",
            "古い→新しい",
            "名前 a→z",
            "名前 z→a",
            "拡張子 a→z",
            "拡張子 z→a",
            "小さい→大きい",
            "大きい→小さい",
            "新しい→古い 更新日時",
            "古い→新しい 更新日時",
            "ランダム"});
			this.SortOrder.Location = new System.Drawing.Point(27, 477);
			this.SortOrder.Name = "SortOrder";
			this.SortOrder.Size = new System.Drawing.Size(189, 32);
			this.SortOrder.TabIndex = 21;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label3.Location = new System.Drawing.Point(23, 450);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(122, 24);
			this.label3.TabIndex = 20;
			this.label3.Text = "ソートオーダー";
			// 
			// NoUpFavicon
			// 
			this.NoUpFavicon.AutoSize = true;
			this.NoUpFavicon.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.NoUpFavicon.Location = new System.Drawing.Point(498, 366);
			this.NoUpFavicon.Name = "NoUpFavicon";
			this.NoUpFavicon.Size = new System.Drawing.Size(240, 28);
			this.NoUpFavicon.TabIndex = 26;
			this.NoUpFavicon.Text = "favicon.icoアップロード禁止";
			this.NoUpFavicon.UseVisualStyleBackColor = true;
			// 
			// EditWin
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(761, 559);
			this.Controls.Add(this.MovieMusicEmbedBtn);
			this.Controls.Add(this.NoUpFavicon);
			this.Controls.Add(this.UploadDirデフォルトBtn);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.SortOrder);
			this.Controls.Add(this.ShowDownloadLinkFlag);
			this.Controls.Add(this.PortNoデフォルトBtn);
			this.Controls.Add(this.デフォルトBtn);
			this.Controls.Add(this.NoOverwriteFlag);
			this.Controls.Add(this.UploadedFileNumMaxデフォルトBtn);
			this.Controls.Add(this.Password);
			this.Controls.Add(this.PasswordEnabled);
			this.Controls.Add(this.UploadDiskFreeMinデフォルトBtn);
			this.Controls.Add(this.UploadDirSizeMaxデフォルトBtn);
			this.Controls.Add(this.画像の表示Grp);
			this.Controls.Add(this.ShowDeleteButtonFlag);
			this.Controls.Add(this.label8);
			this.Controls.Add(this.label9);
			this.Controls.Add(this.UploadDirSizeMax);
			this.Controls.Add(this.DateLangJ);
			this.Controls.Add(this.label7);
			this.Controls.Add(this.UploadedFileNumMax);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.UploadDiskFreeMin);
			this.Controls.Add(this.リセットBtn);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.UploadDir);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.PortNo);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "EditWin";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Uploader / 設定";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.EditWin_FormClosed);
			this.Load += new System.EventHandler(this.EditWin_Load);
			this.Shown += new System.EventHandler(this.EditWin_Shown);
			this.画像の表示Grp.ResumeLayout(false);
			this.画像の表示Grp.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox PortNo;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox UploadDir;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button リセットBtn;
		private System.Windows.Forms.TextBox UploadDiskFreeMin;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox UploadedFileNumMax;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.CheckBox DateLangJ;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.TextBox UploadDirSizeMax;
		private System.Windows.Forms.CheckBox ShowDeleteButtonFlag;
		private System.Windows.Forms.ToolTip ToolTips;
		private System.Windows.Forms.GroupBox 画像の表示Grp;
		private System.Windows.Forms.Label 画像ラベル2;
		private System.Windows.Forms.TextBox ImageExts;
		private System.Windows.Forms.Label 画像ラベル1_1;
		private System.Windows.Forms.CheckBox ShowImageFlag;
		private System.Windows.Forms.Label 画像ラベル1;
		private System.Windows.Forms.TextBox ShowedImageTotalSizeMax;
		private System.Windows.Forms.Button UploadDirSizeMaxデフォルトBtn;
		private System.Windows.Forms.Button UploadDiskFreeMinデフォルトBtn;
		private System.Windows.Forms.CheckBox PasswordEnabled;
		private System.Windows.Forms.TextBox Password;
		private System.Windows.Forms.Button UploadedFileNumMaxデフォルトBtn;
		private System.Windows.Forms.CheckBox NoOverwriteFlag;
		private System.Windows.Forms.Button デフォルトBtn;
		private System.Windows.Forms.Button ShowedImageTotalSizeMaxデフォルトBtn;
		private System.Windows.Forms.Button PortNoデフォルトBtn;
		private System.Windows.Forms.CheckBox ShowDownloadLinkFlag;
		private System.Windows.Forms.ComboBox SortOrder;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Button UploadDirデフォルトBtn;
		private System.Windows.Forms.CheckBox NoUpFavicon;
		private System.Windows.Forms.Button MovieMusicEmbedBtn;
	}
}
