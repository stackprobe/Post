namespace Uploader
{
	partial class MovieMusicEmbedDlg
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MovieMusicEmbedDlg));
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.MovieExtsLabel = new System.Windows.Forms.Label();
			this.MovieExts = new System.Windows.Forms.TextBox();
			this.EmbedMovieFlag = new System.Windows.Forms.CheckBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.MusicExtsLabel = new System.Windows.Forms.Label();
			this.MusicExts = new System.Windows.Forms.TextBox();
			this.EmbedMusicFlag = new System.Windows.Forms.CheckBox();
			this.ToolTips = new System.Windows.Forms.ToolTip(this.components);
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox1.Controls.Add(this.MovieExtsLabel);
			this.groupBox1.Controls.Add(this.MovieExts);
			this.groupBox1.Controls.Add(this.EmbedMovieFlag);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(470, 120);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "動画の埋め込み";
			// 
			// MovieExtsLabel
			// 
			this.MovieExtsLabel.AutoSize = true;
			this.MovieExtsLabel.Location = new System.Drawing.Point(6, 59);
			this.MovieExtsLabel.Name = "MovieExtsLabel";
			this.MovieExtsLabel.Size = new System.Drawing.Size(139, 20);
			this.MovieExtsLabel.TabIndex = 1;
			this.MovieExtsLabel.Text = "動画ファイルの拡張子";
			// 
			// MovieExts
			// 
			this.MovieExts.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.MovieExts.Location = new System.Drawing.Point(151, 56);
			this.MovieExts.MaxLength = 1000;
			this.MovieExts.Name = "MovieExts";
			this.MovieExts.Size = new System.Drawing.Size(313, 27);
			this.MovieExts.TabIndex = 2;
			this.MovieExts.Text = "ext.ext.ext";
			this.ToolTips.SetToolTip(this.MovieExts, "拡張子を半角ピリオドで区切って記述して下さい。");
			// 
			// EmbedMovieFlag
			// 
			this.EmbedMovieFlag.AutoSize = true;
			this.EmbedMovieFlag.Location = new System.Drawing.Point(151, 26);
			this.EmbedMovieFlag.Name = "EmbedMovieFlag";
			this.EmbedMovieFlag.Size = new System.Drawing.Size(119, 24);
			this.EmbedMovieFlag.TabIndex = 0;
			this.EmbedMovieFlag.Text = "動画を埋め込む";
			this.EmbedMovieFlag.UseVisualStyleBackColor = true;
			this.EmbedMovieFlag.CheckedChanged += new System.EventHandler(this.EmbedMovieFlag_CheckedChanged);
			// 
			// groupBox2
			// 
			this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox2.Controls.Add(this.MusicExtsLabel);
			this.groupBox2.Controls.Add(this.MusicExts);
			this.groupBox2.Controls.Add(this.EmbedMusicFlag);
			this.groupBox2.Location = new System.Drawing.Point(12, 138);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(470, 120);
			this.groupBox2.TabIndex = 1;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "音楽の埋め込み";
			// 
			// MusicExtsLabel
			// 
			this.MusicExtsLabel.AutoSize = true;
			this.MusicExtsLabel.Location = new System.Drawing.Point(6, 59);
			this.MusicExtsLabel.Name = "MusicExtsLabel";
			this.MusicExtsLabel.Size = new System.Drawing.Size(139, 20);
			this.MusicExtsLabel.TabIndex = 1;
			this.MusicExtsLabel.Text = "音楽ファイルの拡張子";
			// 
			// MusicExts
			// 
			this.MusicExts.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.MusicExts.Location = new System.Drawing.Point(151, 56);
			this.MusicExts.MaxLength = 1000;
			this.MusicExts.Name = "MusicExts";
			this.MusicExts.Size = new System.Drawing.Size(313, 27);
			this.MusicExts.TabIndex = 2;
			this.MusicExts.Text = "ext.ext.ext";
			this.ToolTips.SetToolTip(this.MusicExts, "拡張子を半角ピリオドで区切って記述して下さい。");
			// 
			// EmbedMusicFlag
			// 
			this.EmbedMusicFlag.AutoSize = true;
			this.EmbedMusicFlag.Location = new System.Drawing.Point(151, 26);
			this.EmbedMusicFlag.Name = "EmbedMusicFlag";
			this.EmbedMusicFlag.Size = new System.Drawing.Size(119, 24);
			this.EmbedMusicFlag.TabIndex = 0;
			this.EmbedMusicFlag.Text = "音楽を埋め込む";
			this.EmbedMusicFlag.UseVisualStyleBackColor = true;
			this.EmbedMusicFlag.CheckedChanged += new System.EventHandler(this.EmbedMusicFlag_CheckedChanged);
			// 
			// MovieMusicEmbedDlg
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(494, 291);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Font = new System.Drawing.Font("メイリオ", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "MovieMusicEmbedDlg";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Uploader / 設定 / 動画・音楽ファイルの埋め込み";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MovieMusicEmbedDlg_FormClosing);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MovieMusicEmbedDlg_FormClosed);
			this.Load += new System.EventHandler(this.MovieMusicEmbedDlg_Load);
			this.Shown += new System.EventHandler(this.MovieMusicEmbedDlg_Shown);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label MovieExtsLabel;
		private System.Windows.Forms.TextBox MovieExts;
		private System.Windows.Forms.CheckBox EmbedMovieFlag;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Label MusicExtsLabel;
		private System.Windows.Forms.TextBox MusicExts;
		private System.Windows.Forms.CheckBox EmbedMusicFlag;
		private System.Windows.Forms.ToolTip ToolTips;
	}
}
