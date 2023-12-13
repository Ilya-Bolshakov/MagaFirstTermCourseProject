#pragma once
#include "Methods.h"
#include "Loader.h"


namespace MagaFirstTermCourseProjectFormsApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace System::Threading;

	using namespace CommonTypes;
	using namespace KMeansSequential;
	using namespace KMeansOpenMP;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//

			SetStartButtonState();
			this->loader = gcnew Loader();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox;


	private: System::Windows::Forms::Button^ buttonStart;
	private: System::Windows::Forms::PictureBox^ pictureBox;

	private: System::Windows::Forms::MenuStrip^ menuStrip;

	private: System::Windows::Forms::ToolStripMenuItem^ ToolStripMenuItemFile;
	private: System::Windows::Forms::ToolStripMenuItem^ ToolStripMenuItemFileOpen;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;

	protected:
		Bitmap^ file;
		Method^ method;
		String^ currentTextInTextBox;
		Loader^ loader;
		Bitmap^ clusteredImage;
	private: System::Windows::Forms::PictureBox^ pictureBoxResult;
	private: System::Windows::Forms::ComboBox^ comboBoxMethods;
	private: System::Windows::Forms::ToolStripMenuItem^ healthChecksToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openMPHealthCheckToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::Label^ labelSelectMethod;
	private: System::Windows::Forms::Label^ labelClustersNumber;
	private: System::Windows::Forms::ErrorProvider^ errorProvider;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorkerImage;
	private: System::Windows::Forms::ToolStripMenuItem^ cudaHealthCheckToolStripMenuItem;
	private: System::ComponentModel::IContainer^ components;

	protected:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->textBox = (gcnew System::Windows::Forms::TextBox());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->ToolStripMenuItemFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItemFileOpen = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->healthChecksToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openMPHealthCheckToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBoxResult = (gcnew System::Windows::Forms::PictureBox());
			this->comboBoxMethods = (gcnew System::Windows::Forms::ComboBox());
			this->labelSelectMethod = (gcnew System::Windows::Forms::Label());
			this->labelClustersNumber = (gcnew System::Windows::Forms::Label());
			this->errorProvider = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorkerImage = (gcnew System::ComponentModel::BackgroundWorker());
			this->cudaHealthCheckToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->menuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxResult))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox
			// 
			this->textBox->Location = System::Drawing::Point(282, 633);
			this->textBox->Name = L"textBox";
			this->textBox->Size = System::Drawing::Size(211, 20);
			this->textBox->TabIndex = 0;
			this->textBox->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox_TextChanged);
			this->textBox->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::textBox_Validating);
			// 
			// buttonStart
			// 
			this->buttonStart->Location = System::Drawing::Point(22, 746);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(139, 53);
			this->buttonStart->TabIndex = 2;
			this->buttonStart->Text = L"Запуск";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &MainForm::buttonStart_Click);
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(22, 29);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(619, 537);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox->TabIndex = 3;
			this->pictureBox->TabStop = false;
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ToolStripMenuItemFile,
					this->healthChecksToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(1604, 24);
			this->menuStrip->TabIndex = 4;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// ToolStripMenuItemFile
			// 
			this->ToolStripMenuItemFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ToolStripMenuItemFileOpen,
					this->exitToolStripMenuItem
			});
			this->ToolStripMenuItemFile->Name = L"ToolStripMenuItemFile";
			this->ToolStripMenuItemFile->Size = System::Drawing::Size(48, 20);
			this->ToolStripMenuItemFile->Text = L"Файл";
			// 
			// ToolStripMenuItemFileOpen
			// 
			this->ToolStripMenuItemFileOpen->Name = L"ToolStripMenuItemFileOpen";
			this->ToolStripMenuItemFileOpen->Size = System::Drawing::Size(121, 22);
			this->ToolStripMenuItemFileOpen->Text = L"Открыть";
			this->ToolStripMenuItemFileOpen->Click += gcnew System::EventHandler(this, &MainForm::ToolStripMenuItemFileOpen_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(121, 22);
			this->exitToolStripMenuItem->Text = L"Выход";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// healthChecksToolStripMenuItem
			// 
			this->healthChecksToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openMPHealthCheckToolStripMenuItem,
					this->cudaHealthCheckToolStripMenuItem
			});
			this->healthChecksToolStripMenuItem->Name = L"healthChecksToolStripMenuItem";
			this->healthChecksToolStripMenuItem->Size = System::Drawing::Size(92, 20);
			this->healthChecksToolStripMenuItem->Text = L"HealthChecks";
			// 
			// openMPHealthCheckToolStripMenuItem
			// 
			this->openMPHealthCheckToolStripMenuItem->Name = L"openMPHealthCheckToolStripMenuItem";
			this->openMPHealthCheckToolStripMenuItem->Size = System::Drawing::Size(195, 22);
			this->openMPHealthCheckToolStripMenuItem->Text = L"OpenMP Health Check";
			this->openMPHealthCheckToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openMPHealthCheckToolStripMenuItem_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog";
			this->openFileDialog->Filter = L"\"Images (bmp, jpg, jpeg)|*.jpg;*.bmp;*.jpeg\"";
			// 
			// pictureBoxResult
			// 
			this->pictureBoxResult->Location = System::Drawing::Point(836, 29);
			this->pictureBoxResult->Name = L"pictureBoxResult";
			this->pictureBoxResult->Size = System::Drawing::Size(636, 537);
			this->pictureBoxResult->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBoxResult->TabIndex = 5;
			this->pictureBoxResult->TabStop = false;
			// 
			// comboBoxMethods
			// 
			this->comboBoxMethods->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxMethods->FormattingEnabled = true;
			this->comboBoxMethods->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				L"KMeans последовательный", L"KMeans через OpenMP",
					L"KMeans через Cuda"
			});
			this->comboBoxMethods->Location = System::Drawing::Point(282, 675);
			this->comboBoxMethods->Name = L"comboBoxMethods";
			this->comboBoxMethods->Size = System::Drawing::Size(211, 21);
			this->comboBoxMethods->TabIndex = 6;
			this->comboBoxMethods->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBoxMethods_SelectedIndexChanged);
			// 
			// labelSelectMethod
			// 
			this->labelSelectMethod->AutoSize = true;
			this->labelSelectMethod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelSelectMethod->Location = System::Drawing::Point(19, 676);
			this->labelSelectMethod->Name = L"labelSelectMethod";
			this->labelSelectMethod->Size = System::Drawing::Size(142, 20);
			this->labelSelectMethod->TabIndex = 7;
			this->labelSelectMethod->Text = L"Выберите метод:";
			// 
			// labelClustersNumber
			// 
			this->labelClustersNumber->AutoSize = true;
			this->labelClustersNumber->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->labelClustersNumber->Location = System::Drawing::Point(19, 631);
			this->labelClustersNumber->Name = L"labelClustersNumber";
			this->labelClustersNumber->Size = System::Drawing::Size(257, 20);
			this->labelClustersNumber->TabIndex = 8;
			this->labelClustersNumber->Text = L"Введите количество кластеров:";
			// 
			// errorProvider
			// 
			this->errorProvider->ContainerControl = this;
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker_DoWork);
			this->backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorker_RunWorkerCompleted);
			// 
			// backgroundWorkerImage
			// 
			this->backgroundWorkerImage->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorkerImage_DoWork);
			this->backgroundWorkerImage->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorkerImage_RunWorkerCompleted);
			// 
			// cudaHealthCheckToolStripMenuItem
			// 
			this->cudaHealthCheckToolStripMenuItem->Name = L"cudaHealthCheckToolStripMenuItem";
			this->cudaHealthCheckToolStripMenuItem->Size = System::Drawing::Size(195, 22);
			this->cudaHealthCheckToolStripMenuItem->Text = L"Cuda Health Check";
			this->cudaHealthCheckToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::cudaHealthCheckToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1604, 961);
			this->Controls->Add(this->labelClustersNumber);
			this->Controls->Add(this->labelSelectMethod);
			this->Controls->Add(this->comboBoxMethods);
			this->Controls->Add(this->pictureBoxResult);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->buttonStart);
			this->Controls->Add(this->textBox);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Кластеризация изображений";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxResult))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonStart_Click(System::Object^ sender, System::EventArgs^ e) {
		
		loader->Show();
		this->Enabled = false;
		backgroundWorkerImage->RunWorkerAsync();
	}

	private: System::Void ToolStripMenuItemFileOpen_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			this->Enabled = false;
			backgroundWorker->RunWorkerAsync();
		}
	}

	private: std::vector<Pixel> GetPixels()
	{
		std::vector<Pixel> pixels;

		for (size_t i = 0; i < file->Height; i++)
		{
			for (size_t j = 0; j < file->Width; j++)
			{
				Pixel pixel;
				pixel.r = file->GetPixel(j, i).R;
				pixel.g = file->GetPixel(j, i).G;
				pixel.b = file->GetPixel(j, i).B;
				pixels.push_back(pixel);
			}
		}

		return pixels;
	}
	private: System::Void comboBoxMethods_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		auto factory = gcnew MethodSimpleFactory();

		method = factory->GetMethod(comboBoxMethods->SelectedIndex);

		SetStartButtonState();
	}

	private: void SetStartButtonState()
	{
		buttonStart->Enabled = method != nullptr && file != nullptr;
	}

	private: System::Void openMPHealthCheckToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
#ifdef _OPENMP
		MessageBox::Show("OpenMP работает!");
		return;
#endif
		MessageBox::Show("OpenMP не работает!");

	}
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
private: System::Void textBox_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	if (String::IsNullOrEmpty(textBox->Text))
	{
		e->Cancel = true;
		errorProvider->SetError(textBox, "Введите количество кластеров!");
		textBox->SelectionStart = textBox->Text->Length;
		return;
	}

	int result;

	if (Int32::TryParse(textBox->Text, result))
	{
		e->Cancel = false;
		errorProvider->SetError(textBox, nullptr);
		currentTextInTextBox = textBox->Text;
	}
	else
	{
		textBox->Text = this->currentTextInTextBox;
		e->Cancel = true;
		errorProvider->SetError(textBox, "Введите количество кластеров!");
		textBox->SelectionStart = textBox->Text->Length;
	}

}
private: System::Void textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	this->ValidateChildren();
	SetStartButtonState();
}

private: System::Void backgroundWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	try
	{
		this->file = gcnew Bitmap(Bitmap::FromFile(openFileDialog->FileName));
		pictureBox->Image = file;
	}
	catch (System::Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}

	
}
private: System::Void backgroundWorker_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
	loader->Hide();
	this->Enabled = true;
	this->Focus();
	SetStartButtonState();
}
private: System::Void backgroundWorkerImage_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	auto sw = gcnew Stopwatch();
	sw->Start();

	auto pixels = GetPixels();
	auto image = method->KMeans(pixels, Convert::ToInt32(textBox->Text));

	sw->Stop();

	Bitmap^ clusteredImage = gcnew Bitmap(file->Width, file->Height);

	for (int i = 0; i < file->Width; i++)
	{
		for (int j = 0; j < file->Height; j++)
		{
			int centroidIndex = image.assignments[j * file->Width + i];
			if (centroidIndex >= 0 && centroidIndex < image.centroids.size())
			{
				Color newColor = Color::FromArgb(image.centroids[centroidIndex].r, image.centroids[centroidIndex].g, image.centroids[centroidIndex].b);
				clusteredImage->SetPixel(i, j, newColor);
			}
			else
			{
				throw gcnew Exception("wdwd");
			}
		}
	}

	this->clusteredImage = clusteredImage;

	auto ts = TimeSpan::FromMilliseconds(sw->ElapsedMilliseconds);

	auto str = String::Format("Кластеризация окончена\nМетод: {0}\nКоличество кластеров: {1}\nВремя: {2} секунд", method->name, textBox->Text, ts.TotalSeconds);

	MessageBox::Show(str);
}
private: System::Void backgroundWorkerImage_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
	loader->Hide();
	this->Enabled = true;
	this->Focus();
	pictureBoxResult->Image = clusteredImage;

}
private: System::Void cudaHealthCheckToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	auto hc = gcnew CudaMethod();
	auto ok = hc->HealthCheck();

	String^ info = "Cuda ";

	if (ok)
	{
		info += "работает!";
	}
	else
	{
		info += "не работает!";
	}

	MessageBox::Show(info);
}
};
}
