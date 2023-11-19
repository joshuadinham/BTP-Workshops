// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"
#include <algorithm>
#include <memory>

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//         The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Raw Pointers.
		bool found = false;
		Profile* p{};
		for (size_t i = 0; i < allProfiles.size(); i++)
		{
			for (size_t j = 0; j < bannedProfiles.size() && found != true; j++)
			{
				found = ((allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) && (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name) && (allProfiles[i].m_age == bannedProfiles[j].m_age));

			}
			if (!found)
			{

				p = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
				if (p->validateAddrress())
					result += p;
				delete p;

			}
			found = false;

		}
		return result;
	}
		DataBase<Profile> excludeSmart(const DataBase<Profile>&allProfiles, const DataBase<Profile>&bannedProfiles) {
			DataBase<Profile> result;
			// TODO: Add your code here to build a collection of Profiles.
			//		   The result should contain only profiles from `allProfiles`
			//         which are not in `bannedProfiles` using Smart Pointers.
			bool found = false;
			
			for (size_t i = 0; i < allProfiles.size(); i++)
			{
				for (size_t j = 0; j < bannedProfiles.size() && found != true; j++)
				{
					found = ((allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) && (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name) && (allProfiles[i].m_age == bannedProfiles[j].m_age));

				}
				if (!found)
				{

					std::shared_ptr<Profile> ptr(new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age));
					if (ptr->validateAddrress())
						result += ptr;
					

				}
				found = false;

			}

			return result;
		}
	
}
