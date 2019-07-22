// (C) 2019 Transport for London
// All rights reserved.  This information is confidential.  You may not
// reproduce, adapt or disclose this information or any part of the
// information, for any purpose without TfL’s written permission.  TfL
// makes no warranties or representations, and expressly disclaims all
// liability concerning this information


#ifndef TNR_ENUMERATIONSTORE_H
#define TNR_ENUMERATIONSTORE_H


#include <string>
#include <memory>
#include <vector>

class EnumerationStore
{
public:
    EnumerationStore();
    virtual ~EnumerationStore();

public:
    //! Adds the identifier to the list of enumerations with the next value
    void AddEnumValue(const std::string &enumName);
    //! Sets last enumeration to enumValue and future enums will increment the value
    void SetEnumValue(uint32_t enumValue);
    //! Returns name corresponding to the value or an empty string
    std::string GetEnumName(uint32_t enumValue);
    //! Debug method
    void PrintEnumStore();
private:
    std::vector<std::pair<uint32_t, std::string>> m_enumeration;

};

typedef std::shared_ptr<EnumerationStore> EnumerationStore_ptr;

#endif //TNR_ENUMERATIONSTORE_H
