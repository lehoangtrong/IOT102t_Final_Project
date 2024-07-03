
namespace StudentManager
{
    partial class FingerStudent
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
            label3 = new Label();
            textBoxName = new TextBox();
            textBoxStudentID = new TextBox();
            nameStudent = new Label();
            studentId = new Label();
            SuspendLayout();
            // 
            // Status
            // 
            Status.AutoSize = true;
            Status.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            Status.Location = new Point(12, 22);
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
            statusLabel.Location = new Point(86, 22);
            statusLabel.Name = "statusLabel";
            statusLabel.Size = new Size(198, 30);
            statusLabel.TabIndex = 1;
            statusLabel.Text = "Đang tìm ESP8266...";
            // 
            // addButton
            // 
            addButton.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            addButton.Location = new Point(878, 40);
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
            serialOutput.Font = new Font("Segoe UI", 15F, FontStyle.Regular, GraphicsUnit.Point);
            serialOutput.Location = new Point(23, 136);
            serialOutput.Multiline = true;
            serialOutput.Name = "serialOutput";
            serialOutput.ReadOnly = true;
            serialOutput.ScrollBars = ScrollBars.Vertical;
            serialOutput.Size = new Size(1054, 428);
            serialOutput.TabIndex = 4;
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
            textBoxName.ForeColor = Color.Gray;
            textBoxName.Location = new Point(535, 26);
            textBoxName.Name = "textBoxName";
            textBoxName.Size = new Size(320, 29);
            textBoxName.TabIndex = 7;
            textBoxName.Text = "Nhập tên sinh viên";
            textBoxName.Enter += textBoxName_Enter;
            textBoxName.Leave += textBoxName_Leave;
            // 
            // textBoxStudentID
            // 
            textBoxStudentID.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            textBoxStudentID.ForeColor = Color.Gray;
            textBoxStudentID.Location = new Point(535, 62);
            textBoxStudentID.Name = "textBoxStudentID";
            textBoxStudentID.Size = new Size(320, 29);
            textBoxStudentID.TabIndex = 8;
            textBoxStudentID.Text = "Nhập mã sinh viên";
            textBoxStudentID.Enter += textBoxStudentID_Enter;
            textBoxStudentID.Leave += textBoxStudentID_Leave;
            // 
            // nameStudent
            // 
            nameStudent.AutoSize = true;
            nameStudent.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            nameStudent.Location = new Point(341, 22);
            nameStudent.Name = "nameStudent";
            nameStudent.Size = new Size(188, 30);
            nameStudent.TabIndex = 10;
            nameStudent.Text = "Nhập tên sinh viên";
            // 
            // studentId
            // 
            studentId.AutoSize = true;
            studentId.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            studentId.Location = new Point(341, 61);
            studentId.Name = "studentId";
            studentId.Size = new Size(187, 30);
            studentId.TabIndex = 11;
            studentId.Text = "Nhập mã sinh viên";
            // 
            // FingerStudent
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1099, 637);
            Controls.Add(studentId);
            Controls.Add(nameStudent);
            Controls.Add(textBoxStudentID);
            Controls.Add(textBoxName);
            Controls.Add(label3);
            Controls.Add(serialOutput);
            Controls.Add(clearButton);
            Controls.Add(addButton);
            Controls.Add(statusLabel);
            Controls.Add(Status);
            Name = "FingerStudent";
            Text = "FingerStudent";
            ResumeLayout(false);
            PerformLayout();
        }

        private void textBoxStudentID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxStudentID.Text))
            {
                textBoxStudentID.Text = "Nhập mã sinh viên";
                textBoxStudentID.ForeColor = Color.Gray;
            }
        }

        private void textBoxStudentID_Enter(object sender, EventArgs e)
        {
            if (textBoxStudentID.Text == "Nhập mã sinh viên")
            {
                textBoxStudentID.Text = "";
                textBoxStudentID.ForeColor = Color.Black;
            }
        }

        private void textBoxName_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxName.Text))
            {
                textBoxName.Text = "Nhập tên sinh viên";
                textBoxName.ForeColor = Color.Gray;
            }
        }

        private void textBoxName_Enter(object sender, EventArgs e)
        {
            if (textBoxName.Text == "Nhập tên sinh viên")
            {
                textBoxName.Text = "";
                textBoxName.ForeColor = Color.Black;
            }
        }

        #endregion

        private Label Status;
        private Label statusLabel;
        private Button addButton;
        private Button clearButton;
        private TextBox serialOutput;
        private Label label3;
        private TextBox textBoxName;
        private TextBox textBoxStudentID;
        private Label nameStudent;
        private Label studentId;
    }
}
