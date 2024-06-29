namespace StudentManager
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            Status = new Label();
            statusLabel = new Label();
            addButton = new Button();
            clearButton = new Button();
            serialOutput = new TextBox();
            dataStudent = new DataGridView();
            label3 = new Label();
            textBoxName = new TextBox();
            textBoxStudentID = new TextBox();
            label1 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataStudent).BeginInit();
            SuspendLayout();
            // 
            // Status
            // 
            Status.AutoSize = true;
            Status.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            Status.Location = new Point(23, 26);
            Status.Name = "Status";
            Status.Size = new Size(80, 30);
            Status.TabIndex = 0;
            Status.Text = "Status: ";
            // 
            // statusLabel
            // 
            statusLabel.AutoSize = true;
            statusLabel.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            statusLabel.ForeColor = Color.Red;
            statusLabel.Location = new Point(98, 26);
            statusLabel.Name = "statusLabel";
            statusLabel.Size = new Size(194, 30);
            statusLabel.TabIndex = 1;
            statusLabel.Text = "Đang tìm Arduino...";
            // 
            // addButton
            // 
            addButton.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            addButton.Location = new Point(880, 28);
            addButton.Name = "addButton";
            addButton.Size = new Size(199, 40);
            addButton.TabIndex = 2;
            addButton.Text = "Thêm Sinh Viên";
            addButton.UseVisualStyleBackColor = true;
            addButton.Click += addButton_Click;
            // 
            // clearButton
            // 
            clearButton.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            clearButton.Location = new Point(30, 570);
            clearButton.Name = "clearButton";
            clearButton.Size = new Size(136, 40);
            clearButton.TabIndex = 3;
            clearButton.Text = "Xóa Log";
            clearButton.UseVisualStyleBackColor = true;
            clearButton.Click += clearButton_Click;
            // 
            // serialOutput
            // 
            serialOutput.Location = new Point(23, 136);
            serialOutput.Multiline = true;
            serialOutput.Name = "serialOutput";
            serialOutput.ReadOnly = true;
            serialOutput.ScrollBars = ScrollBars.Vertical;
            serialOutput.Size = new Size(507, 428);
            serialOutput.TabIndex = 4;
            // 
            // dataStudent
            // 
            dataStudent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataStudent.Location = new Point(558, 136);
            dataStudent.Name = "dataStudent";
            dataStudent.RowTemplate.Height = 25;
            dataStudent.Size = new Size(507, 428);
            dataStudent.TabIndex = 5;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            label3.Location = new Point(30, 98);
            label3.Name = "label3";
            label3.Size = new Size(143, 30);
            label3.TabIndex = 6;
            label3.Text = "Serial Monitor";
            // 
            // textBoxName
            // 
            textBoxName.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            textBoxName.Location = new Point(362, 26);
            textBoxName.Name = "textBoxName";
            textBoxName.Size = new Size(493, 29);
            textBoxName.TabIndex = 7;
            textBoxName.Text = "Nhập tên sinh viên";
            // 
            // textBoxStudentID
            // 
            textBoxStudentID.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            textBoxStudentID.Location = new Point(362, 61);
            textBoxStudentID.Name = "textBoxStudentID";
            textBoxStudentID.Size = new Size(493, 29);
            textBoxStudentID.TabIndex = 8;
            textBoxStudentID.Text = "Nhập mã Sinh Viên";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            label1.Location = new Point(558, 98);
            label1.Name = "label1";
            label1.Size = new Size(236, 30);
            label1.TabIndex = 9;
            label1.Text = "Sinh viên có trong CSDL";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1099, 637);
            Controls.Add(label1);
            Controls.Add(textBoxStudentID);
            Controls.Add(textBoxName);
            Controls.Add(label3);
            Controls.Add(dataStudent);
            Controls.Add(serialOutput);
            Controls.Add(clearButton);
            Controls.Add(addButton);
            Controls.Add(statusLabel);
            Controls.Add(Status);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)dataStudent).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label Status;
        private Label statusLabel;
        private Button addButton;
        private Button clearButton;
        private TextBox serialOutput;
        private DataGridView dataStudent;
        private Label label3;
        private TextBox textBoxName;
        private TextBox textBoxStudentID;
        private Label label1;
    }
}
