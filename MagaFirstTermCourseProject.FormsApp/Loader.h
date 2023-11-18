#pragma once

namespace MagaFirstTermCourseProjectFormsApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� Loader
	/// </summary>
	public ref class Loader : public System::Windows::Forms::Form
	{
	public:
		Loader(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//

			auto bm = gcnew Bitmap("1485.gif");
			RotatingBlocks = gcnew Bitmap("Gear.gif");

			DrawHere = Point(10, 10);
			InvalidRect = System::Drawing::Rectangle(DrawHere, RotatingBlocks->Size);

			this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
			this->SetStyle(ControlStyles::DoubleBuffer, true);
		}

		Bitmap^ RotatingBlocks;
		Point DrawHere;
		System::Drawing::Rectangle InvalidRect;

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~Loader()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Loader
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(72, 90);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Loader";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Loader";
			this->Load += gcnew System::EventHandler(this, &Loader::Loader_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Loader_Load(System::Object^ sender, System::EventArgs^ e) {
		if (ImageAnimator::CanAnimate(RotatingBlocks))
		{

			ImageAnimator::Animate(RotatingBlocks,
				gcnew System::EventHandler(this, &Loader::OnFrameChanged));


		}
	}

	protected: void OnPaint(PaintEventArgs^ e) override
		   {
			   ImageAnimator::UpdateFrames(RotatingBlocks);

			   e->Graphics->DrawImage(RotatingBlocks, DrawHere);
		   }

	private: virtual void OnFrameChanged(Object^ o, EventArgs^ e)
		   {

			   this->Invalidate(InvalidRect);
		   }
	};
}
