#ifndef _VOCABULARY_H
#define _VOCABULARY_H

#include <vector>

struct vocab_entry
{
	vocab_entry(int n);
	std::string v_question;
	std::string v_answer;
	int v_goal;

	int v_attempted;
	int v_failed;
	bool v_finished;
};


class vocabulary 
{
	public:
		vocabulary();
		~vocabulary();

		void load_vocab();

		void load_history();

		void ask();

		bool is_done();
	private:
		std::vector<vocab_entry> m_vocab;
		std::vector<vocab_entry> m_inactive;
		int m_notdone;

		void fix_testing();	
		int find_entry(int n);
	protected:
		int test(std::string s);
};

#endif /*_VOCABULARY_H*/
