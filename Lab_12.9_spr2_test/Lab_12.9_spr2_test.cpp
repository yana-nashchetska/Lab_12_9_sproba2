#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_9_sproba2/Lab_12_9_sproba2.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab129spr2test
{
	TEST_CLASS(Lab129spr2test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{


		
		
		
		
		//МАХАЛА Я ТОЙ ЮНІТ ТЕСТ ААААААААААААААААААААААААААААААААААААААААААААААААА
		
		
		
		
		void PrintTree(Node * root, int level)
			{
				if (root != NULL)
				{
					PrintTree(root->right, level + 1);
					for (int i = 1; i <= level; i++)
						cout << " ";
					cout << root->info << root->word << endl;
					PrintTree(root->left, level + 1);
				}
			}






		}
	};
}
