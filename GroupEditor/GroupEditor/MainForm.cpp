#include "MainForm.h"
#include "Circle.h"
#include "Rectangle.h"
#include <vcclr.h>
#include <sstream>

using namespace System;

int main()
{
	using namespace System::Windows::Forms;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GroupEditor::MainForm form;
	Application::Run(% form);
	return 0;	
}

std::wstring toWstring(String^ str)
{
	pin_ptr<const wchar_t> wch = PtrToStringChars(str);
	size_t origsize = wcslen(wch) + 1;
	wchar_t* wcstring = new wchar_t[origsize];
	wcscpy_s(wcstring, origsize, wch);
	return std::wstring(wcstring);
}

std::wstring showGroup(const Group* group, std::wstring level)
{
	std::wstring result;
	int i = 1;
	for (const Group& group : *group->getGroups())
	{
		result += level + std::to_wstring(i) + L" " + group.display() + L":\n" + showGroup(&group, level + std::to_wstring(i) + L" ");
		++i;
	}
	for (const Shapes::Shape* shape : *group->getShapes())
	{
		result += level + std::to_wstring(i) + L" " + shape->display() + L"\n";
		++i;
	}
	return result;
}

System::Void GroupEditor::MainForm::commandTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (e->KeyChar == (char)Keys::Enter)
	{
		std::wstring command = toWstring(commandTextBox->Text);
		std::wstringstream in(command);

		getline(in, command, L' ');
		if (command == L"add")
		{
			std::wstring chunk;
			getline(in, chunk, L'[');
			getline(in, chunk, L']');
			Group* currentGroup = mainGroup;
			std::wstringstream levelStream(chunk);
			for (int position; levelStream >> position; )
			{
				if (position >= 1)
				{
					if (position <= currentGroup->getGroups()->size())
					{
						currentGroup = currentGroup->getGroup(position - 1);
					}
					else
					{
						goto COMMAND_ERROR;
					}
				}
			}
			getline(in, chunk, L' ');
			getline(in, chunk, L' ');
			if (chunk == L"group")
			{
				Group group;
				in >> group;
				if (currentGroup->add(group))
				{
					goto GOOD;
				}
				goto COMMAND_ERROR;
			}
			if (chunk == L"circle")
			{
				Shapes::Circle* circle = new Shapes::Circle();
				in >> *circle;
				currentGroup->add(circle);
				goto GOOD;
			}
			if (chunk == L"rect")
			{
				Shapes::Rectangle* rectangle = new Shapes::Rectangle();
				in >> *rectangle;
				currentGroup->add(rectangle);
				goto GOOD;
			}
			goto COMMAND_ERROR;
		}
		if (command == L"del")
		{
			std::wstring chunk;
			getline(in, chunk, L'[');
			getline(in, chunk, L']');
			Group* currentGroup = mainGroup;
			std::wstringstream levelStream(chunk);
			int lastValue;
			if (!(levelStream >> lastValue))
			{
				goto COMMAND_ERROR;
			}
			for (int position = lastValue; levelStream >> lastValue; )
			{
				if (position >= 1)
				{
					if (position <= currentGroup->getGroups()->size())
					{
						currentGroup = currentGroup->getGroup(position - 1);
					}
					else
					{
						goto COMMAND_ERROR;
					}
				}
			}
			if (currentGroup->del(lastValue))
			{
				goto GOOD;
			}
			goto COMMAND_ERROR;
		}
		if (command == L"put")
		{
			std::wstring chunk;
			getline(in, chunk, L'[');
			getline(in, chunk, L']');
			Group* currentGroup = mainGroup;
			std::wstringstream levelStream(chunk);
			for (int position; levelStream >> position; )
			{
				if (position >= 1)
				{
					if (position <= currentGroup->getGroups()->size())
					{
						currentGroup = currentGroup->getGroup(position - 1);
					}
					else
					{
						goto COMMAND_ERROR;
					}
				}
			}
			getline(in, chunk, L' ');
			getline(in, chunk, L'[');
			getline(in, chunk, L']');
			Group* moveGroup = mainGroup;
			levelStream = std::wstringstream(chunk);
			int lastValue;
			if (!(levelStream >> lastValue))
			{
				goto COMMAND_ERROR;
			}
			for (int position = lastValue; levelStream >> lastValue; )
			{
				if (position >= 1)
				{
					if (position <= moveGroup->getGroups()->size())
					{
						moveGroup = moveGroup->getGroup(position - 1);
						continue;
					}
				}
				goto COMMAND_ERROR;
			}
			if (lastValue < 1)
			{
				goto COMMAND_ERROR;
			}
			if (lastValue <= moveGroup->getGroups()->size())
			{
				Group oldGroup = *moveGroup->getGroup(lastValue - 1);
				if (!currentGroup->add(oldGroup))
				{
					goto COMMAND_ERROR;
				}
				moveGroup->del(lastValue);
				goto GOOD;
			}
			if (lastValue > moveGroup->getGroups()->size() + moveGroup->getShapes()->size())
			{
				puts("oh");
				goto COMMAND_ERROR;
			}
			Shapes::Shape* oldShape = *moveGroup->getShape((int)(lastValue - moveGroup->getGroups()->size() - 1));
			if (!currentGroup->add(oldShape))
			{
				goto COMMAND_ERROR;
			}
			moveGroup->del(lastValue);
			goto GOOD;
		}
		if (command == L"copy")
		{
			std::wstring chunk;
			getline(in, chunk, L'[');
			getline(in, chunk, L']');
			Group* currentGroup = mainGroup;
			std::wstringstream levelStream(chunk);
			for (int position; levelStream >> position; )
			{
				if (position >= 1)
				{
					if (position <= currentGroup->getGroups()->size())
					{
						currentGroup = currentGroup->getGroup(position - 1);
					}
					else
					{
						goto COMMAND_ERROR;
					}
				}
			}
			getline(in, chunk, L' ');
			getline(in, chunk, L'[');
			getline(in, chunk, L']');
			Group* moveGroup = mainGroup;
			levelStream = std::wstringstream(chunk);
			int lastValue;
			if (!(levelStream >> lastValue))
			{
				goto COMMAND_ERROR;
			}
			for (int position = lastValue; levelStream >> lastValue; )
			{
				if (position >= 1)
				{
					if (position <= moveGroup->getGroups()->size())
					{
						moveGroup = moveGroup->getGroup(position - 1);
					}
					else
					{
						goto COMMAND_ERROR;
					}
				}
			}
			if (lastValue < 1)
			{
				goto COMMAND_ERROR;
			}
			if (lastValue <= moveGroup->getGroups()->size())
			{
				Group oldGroup = *moveGroup->getGroup(lastValue - 1);
				currentGroup->add(oldGroup);
				goto GOOD;
			}
			if (lastValue > moveGroup->getGroups()->size() + moveGroup->getShapes()->size())
			{
				goto COMMAND_ERROR;
			}
			Shapes::Shape* oldShape = *moveGroup->getShape((int)(lastValue - moveGroup->getGroups()->size() - 1));
			if (!currentGroup->add(oldShape))
			{
				goto COMMAND_ERROR;
			}
			goto GOOD;
		}
		if (command == L"move")
		{
			std::wstring chunk;
			getline(in, chunk, L'[');
			getline(in, chunk, L']');
			Group* currentGroup = mainGroup;
			std::wstringstream levelStream(chunk);
			int lastValue;
			if (!(levelStream >> lastValue))
			{
				goto COMMAND_ERROR;
			}
			for (int position = lastValue; levelStream >> lastValue; )
			{
				if (position >= 1)
				{
					if (position <= currentGroup->getGroups()->size())
					{
						currentGroup = currentGroup->getGroup(position - 1);
					}
					else
					{
						goto COMMAND_ERROR;
					}
				}
			}
			int x, y;
			if (!(in >> x >> y))
			{
				goto COMMAND_ERROR;
			}
			if (lastValue < 1)
			{
				goto COMMAND_ERROR;
			}
			if (lastValue <= currentGroup->getGroups()->size())
			{
				Group* oldGroup = currentGroup->getGroup(lastValue - 1);
				oldGroup->setX(x);
				oldGroup->setY(y);
				/*for (const Group group : *currentGroup->getGroup(lastValue - 1)->getGroups())
				{
					oldGroup.add(group);
				}
				for (Shapes::Shape* group : *currentGroup->getGroup(lastValue - 1)->getShapes())
				{
					oldGroup.add(group);
				}*/
				if (!currentGroup->add(*oldGroup))
				{
					goto COMMAND_ERROR;
				}
				currentGroup->del(lastValue);
				goto GOOD;
			}
			if (lastValue > currentGroup->getGroups()->size() + currentGroup->getShapes()->size())
			{
				goto COMMAND_ERROR;
			}
			Shapes::Shape* oldShape = *currentGroup->getShape((int)(lastValue - currentGroup->getGroups()->size() - 1));
			if (oldShape->getType() == L"Circle")
			{
				Shapes::Circle circle = *(Shapes::Circle*)oldShape;
				circle.setX(x);
				circle.setY(y);

				if (!currentGroup->add(&circle))
				{
					goto COMMAND_ERROR;
				}
				currentGroup->del(lastValue);
				goto GOOD;
			}
			if (oldShape->getType() == L"Rectangle")
			{
				Shapes::Rectangle rectangle = *(Shapes::Rectangle*)oldShape;
				rectangle.setX(x);
				rectangle.setY(y);
				if (!currentGroup->add(&rectangle))
				{
					goto GOOD;
				}
				currentGroup->del(lastValue);
				goto GOOD;
			}
			goto GOOD;
		}
		goto GOOD;
	COMMAND_ERROR:

	GOOD:
		infoLabel->Text = gcnew String(showGroup(mainGroup, L"").c_str());
		commandTextBox->Text = L"";
		canvas->Refresh();
	}
}

void drawGroup(System::Windows::Forms::PaintEventArgs^ e, const Group* group, int xPad, int yPad)
{
	System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
	e->Graphics->DrawRectangle(pen, xPad, yPad, group->getW(), group->getH());
	for (const Group& group : *group->getGroups())
	{
		drawGroup(e, &group, xPad + group.getX(), yPad + group.getY());
	}
	for (const Shapes::Shape* shape : *group->getShapes())
	{
		if (shape->getType() == L"Circle")
		{
			Shapes::Circle* circle = (Shapes::Circle*)shape;
			int x = circle->getX() + xPad;
			int y = circle->getY() + yPad;
			int d = circle->getR() * 2;
			e->Graphics->DrawEllipse(System::Drawing::Pens::BlueViolet, x, y, d, d);
			continue;
		}
		if (shape->getType() == L"Rectangle")
		{
			Shapes::Rectangle* rectangle = (Shapes::Rectangle*)shape;
			int x = rectangle->getX() + xPad;
			int y = rectangle->getY() + yPad;
			int w = rectangle->getW();
			int h = rectangle->getH();
			e->Graphics->DrawRectangle(System::Drawing::Pens::PaleVioletRed, x, y, w, h);
			continue;
		}
	}
}

System::Void GroupEditor::MainForm::canvas_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
	drawGroup(e, mainGroup, mainGroup->getX(), mainGroup->getY());
}
