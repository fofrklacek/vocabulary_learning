#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdio>
#include <ctime>

#include "../include/vocabulary.h"
#define DEFAULT_ENTRY 4

std::string itoa(int n)
{/*{{{*/
	std::string result;
	int dig;
	char digits[][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	for(int i = 1 ;  ; i *=10 )
	{
		if(n / i > 0)
			dig = i;
		else
			break;
	}

	for(; dig > 0; dig/=10)
	{
		result += std::string(digits[n/dig]);
		n %= dig;
	}

	return result;
}/*}}}*/

vocab_entry::vocab_entry(int n = DEFAULT_ENTRY):v_goal(n),v_attempted(0),v_failed(0),v_finished(false)
{/*{{{*/
}/*}}}*/

vocabulary::vocabulary():m_notdone(0)
{/*{{{*/
	std::srand(std::time(nullptr));
}/*}}}*/

vocabulary::~vocabulary()
{/*{{{*/

}/*}}}*/

void vocabulary::load_vocab()
{/*{{{*/
	std::ifstream fr;
	vocab_entry entry;
	std::string filename;
	std::string buffer;

	for(int i = 1 ; ; ++i)
	{
		filename = itoa(i);

		fr.open(std::string("../data/" + filename));

		if(fr.fail())
			break;

		entry.v_question.clear();
		entry.v_answer.clear();

		getline(fr,entry.v_question);		

		while(true)
		{
			getline(fr,buffer);		

			if(fr.eof())
				break;

			entry.v_answer += std::string("\n") + buffer;
		}


		m_vocab.push_back(entry);
		m_notdone += DEFAULT_ENTRY;

		fr.close();
	}

}/*}}}*/

void vocabulary::load_history()
{/*{{{*/

}/*}}}*/

void vocabulary::ask()
{/*{{{*/
	std::string answer;
	int num = std::rand() % m_notdone;
	int entry;

	entry = find_entry(num);

	std::cout << m_vocab[entry].v_question << "\n--------------------------------\n";
	std::cout << "(Success - " << m_vocab[entry].v_attempted - m_vocab[entry].v_failed ;
	std::cout << ",Fail - " << m_vocab[entry].v_failed << ")" << std::endl;
	std::cout << "missing: " << m_vocab[entry].v_goal << std::endl;


	do
	{
		std::cin >> answer;
	}while(test(answer) == -1);

	m_vocab[entry].v_attempted++;

	num = test(answer);

	if(num == 1)
	{
		m_vocab[entry].v_goal--;
		m_notdone--;
		if(m_vocab[entry].v_goal == 0)
		{
			m_vocab[entry].v_finished = true;
			m_inactive.push_back(m_vocab[entry]);
			m_vocab.erase(m_vocab.begin() + entry);
		}
	}
	else if(num == 0)
	{
		m_vocab[entry].v_failed++;
	}


	fix_testing();	

}/*}}}*/

bool vocabulary::is_done()
{/*{{{*/
	std::cout << "Entry remaining: " << m_notdone << ", Group remaining: " << m_vocab.size() << std::endl;
	if(m_vocab.size() == 3 && m_notdone == 3)
	{
		for(auto i : m_vocab)
			if(i.v_finished == false)
				return false;
		return true;
	}

	return false;
}/*}}}*/

int vocabulary::test(std::string s)
{/*{{{*/

	if(s.compare("F") == 0)
		return 0;
	else if(s.compare("S") == 0)
		return 1;
	else
		return -1;
}/*}}}*/

void vocabulary::fix_testing()
{/*{{{*/
	int n;
	if(m_vocab.size() >= 3)
		return;

	n = std::rand() % m_inactive.size();	

	m_inactive[n].v_goal = 1;
	m_vocab.push_back(m_inactive[n]);
	m_inactive.erase(m_inactive.begin() + n);

	m_notdone++;
}/*}}}*/

int vocabulary::find_entry(int n)
{/*{{{*/
	std::vector<vocab_entry>::iterator it = m_vocab.begin();

	for(n -= it->v_goal ; n > 0 ; n -= it->v_goal)
		it++;

	return std::distance(m_vocab.begin(),it);
}/*}}}*/
