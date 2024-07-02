
namespace StudentManager
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            Status = new Label();
            statusLabel = new Label();
            addButton = new Button();
            clearButton = new Button();
            updateButton = new Button();
            serialOutput = new TextBox();
            dataStudent = new DataGridView();
            label3 = new Label();
            textBoxName = new TextBox();
            textBoxStudentID = new TextBox();
            label1 = new Label();
            nameStudent = new Label();
            studentId = new Label();
            No = new DataGridViewTextBoxColumn();
            Name = new DataGridViewTextBoxColumn();
            FingerID = new DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)dataStudent).BeginInit();
            SuspendLayout();
            // 
            // Status
            // 
            Status.AutoSize = true;
            Status.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
<<<<<<< HEAD
            Status.Location = new Point(12, 22);
=======
            Status.Location = new Point(26, 35);
>>>>>>> 0c5c921448d3342880f1666281d4a4152e93b478
            Status.Name = "Status";
            Status.Size = new Size(101, 37);
            Status.TabIndex = 0;
            Status.Text = "Status: ";
            // 
            // statusLabel
            // 
            statusLabel.AutoSize = true;
            statusLabel.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            statusLabel.ForeColor = Color.Red;
<<<<<<< HEAD
            statusLabel.Location = new Point(86, 22);
            statusLabel.Name = "statusLabel";
            statusLabel.Size = new Size(198, 30);
=======
            statusLabel.Location = new Point(112, 35);
            statusLabel.Name = "statusLabel";
            statusLabel.Size = new Size(247, 37);
>>>>>>> 0c5c921448d3342880f1666281d4a4152e93b478
            statusLabel.TabIndex = 1;
            statusLabel.Text = "Đang tìm ESP8266...";
            // 
            // addButton
            // 
            addButton.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
<<<<<<< HEAD
            addButton.Location = new Point(878, 40);
=======
            addButton.Location = new Point(965, 27);
            addButton.Margin = new Padding(3, 4, 3, 4);
>>>>>>> 0c5c921448d3342880f1666281d4a4152e93b478
            addButton.Name = "addButton";
            addButton.Size = new Size(268, 53);
            addButton.TabIndex = 2;
            addButton.Text = "Thêm Sinh Viên";
            addButton.UseVisualStyleBackColor = true;
            addButton.Click += addButton_Click;
            // 
            // clearButton
            // 
            clearButton.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            clearButton.Location = new Point(34, 760);
            clearButton.Margin = new Padding(3, 4, 3, 4);
            clearButton.Name = "clearButton";
            clearButton.Size = new Size(155, 53);
            clearButton.TabIndex = 3;
            clearButton.Text = "Xóa Log";
            clearButton.UseVisualStyleBackColor = true;
            clearButton.Click += clearButton_Click;
            // 
            // updateButton
            // 
            updateButton.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            updateButton.Location = new Point(965, 99);
            updateButton.Margin = new Padding(3, 4, 3, 4);
            updateButton.Name = "updateButton";
            updateButton.Size = new Size(268, 53);
            updateButton.TabIndex = 10;
            updateButton.Text = "Cập Nhật Sinh Viên";
            updateButton.UseVisualStyleBackColor = true;
            updateButton.Click += updateButton_Click;
            // 
            // serialOutput
            // 
<<<<<<< HEAD
            serialOutput.Font = new Font("Segoe UI", 15F, FontStyle.Regular, GraphicsUnit.Point);
            serialOutput.Location = new Point(23, 136);
=======
            serialOutput.Location = new Point(26, 181);
            serialOutput.Margin = new Padding(3, 4, 3, 4);
>>>>>>> 0c5c921448d3342880f1666281d4a4152e93b478
            serialOutput.Multiline = true;
            serialOutput.Name = "serialOutput";
            serialOutput.ReadOnly = true;
            serialOutput.ScrollBars = ScrollBars.Vertical;
            serialOutput.Size = new Size(579, 569);
            serialOutput.TabIndex = 4;
            // 
            // dataStudent
            // 
            dataStudent.BackgroundColor = SystemColors.ButtonHighlight;
            dataStudent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
<<<<<<< HEAD
            dataStudent.Columns.AddRange(new DataGridViewColumn[] { No, Name, FingerID });
            dataStudent.Location = new Point(558, 136);
            dataStudent.MultiSelect = false;
            dataStudent.Name = "dataStudent";
            dataStudent.ReadOnly = true;
=======
            dataStudent.Location = new Point(638, 181);
            dataStudent.Margin = new Padding(3, 4, 3, 4);
            dataStudent.Name = "dataStudent";
            dataStudent.RowHeadersWidth = 51;
>>>>>>> 0c5c921448d3342880f1666281d4a4152e93b478
            dataStudent.RowTemplate.Height = 25;
            dataStudent.Size = new Size(579, 571);
            dataStudent.TabIndex = 5;
            dataStudent.Text = "dataGridView1";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            label3.Location = new Point(34, 131);
            label3.Name = "label3";
            label3.Size = new Size(185, 37);
            label3.TabIndex = 6;
            label3.Text = "Serial Monitor";
            // 
            // textBoxName
            // 
            textBoxName.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
<<<<<<< HEAD
            textBoxName.ForeColor = Color.Gray;
            textBoxName.Location = new Point(535, 26);
            textBoxName.Name = "textBoxName";
            textBoxName.Size = new Size(320, 29);
=======
            textBoxName.Location = new Point(414, 35);
            textBoxName.Margin = new Padding(3, 4, 3, 4);
            textBoxName.Name = "textBoxName";
            textBoxName.Size = new Size(525, 34);
>>>>>>> 0c5c921448d3342880f1666281d4a4152e93b478
            textBoxName.TabIndex = 7;
            textBoxName.Text = "Nhập tên sinh viên";
            textBoxName.Enter += textBoxName_Enter;
            textBoxName.Leave += textBoxName_Leave;
            // 
            // textBoxStudentID
            // 
            textBoxStudentID.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
<<<<<<< HEAD
            textBoxStudentID.ForeColor = Color.Gray;
            textBoxStudentID.Location = new Point(535, 62);
            textBoxStudentID.Name = "textBoxStudentID";
            textBoxStudentID.Size = new Size(320, 29);
=======
            textBoxStudentID.Location = new Point(414, 81);
            textBoxStudentID.Margin = new Padding(3, 4, 3, 4);
            textBoxStudentID.Name = "textBoxStudentID";
            textBoxStudentID.Size = new Size(525, 34);
>>>>>>> 0c5c921448d3342880f1666281d4a4152e93b478
            textBoxStudentID.TabIndex = 8;
            textBoxStudentID.Text = "Nhập mã sinh viên";
            textBoxStudentID.Enter += textBoxStudentID_Enter;
            textBoxStudentID.Leave += textBoxStudentID_Leave;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            label1.Location = new Point(638, 131);
            label1.Name = "label1";
            label1.Size = new Size(301, 37);
            label1.TabIndex = 9;
            label1.Text = "Sinh viên có trong CSDL";
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
            // No
            // 
            No.HeaderText = "Number";
            No.Name = "No";
            No.ReadOnly = true;
            // 
            // Name
            // 
            Name.HeaderText = "Student Name";
            Name.Name = "Name";
            Name.ReadOnly = true;
            // 
            // FingerID
            // 
            FingerID.HeaderText = "Finger Number";
            FingerID.Name = "FingerID";
            FingerID.ReadOnly = true;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
<<<<<<< HEAD
            ClientSize = new Size(1099, 637);
            Controls.Add(studentId);
            Controls.Add(nameStudent);
=======
            ClientSize = new Size(1256, 849);
            Controls.Add(updateButton);
>>>>>>> 0c5c921448d3342880f1666281d4a4152e93b478
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
<<<<<<< HEAD
            Text = "Form1";
=======
            Margin = new Padding(3, 4, 3, 4);
            Name = "Form1";
            Text = "Student Manager";
>>>>>>> 0c5c921448d3342880f1666281d4a4152e93b478
            ((System.ComponentModel.ISupportInitialize)dataStudent).EndInit();
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
        private Button updateButton;  // Thêm khai báo cho updateButton
        private TextBox serialOutput;
        private DataGridView dataStudent;
        private Label label3;
        private TextBox textBoxName;
        private TextBox textBoxStudentID;
        private Label label1;
        private Label nameStudent;
        private Label studentId;
        private DataGridViewTextBoxColumn No;
        private DataGridViewTextBoxColumn Name;
        private DataGridViewTextBoxColumn FingerID;
    }
}
