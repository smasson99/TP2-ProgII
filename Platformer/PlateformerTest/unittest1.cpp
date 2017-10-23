#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Platformer/Testeur.h"
//Il faut que ce dernier lien soit aussi dans 
//[right-click sur projet]\éditeur de liens\propriétés\entrées\dépendances additionnelles
//sinon il y aura une erreur de linkage

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace platformer;

namespace ProjetSFMLTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Testeur testeur;			
			Assert::AreEqual(testeur.testTest(), 0);
		}
	};
}