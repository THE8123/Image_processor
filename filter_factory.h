#ifndef IMAGE_PROCESSOR_FILTER_FACTORY_H
#define IMAGE_PROCESSOR_FILTER_FACTORY_H

// FilterFactory являетт связующим звеном(клеем) между конкретным способом вводом параметров
// в приложении и конечными фильтрами(математическими объектами), поэтому он будет инклюдить их всех
#include <map>

#include "filter.h"
#include "parser.h"
#include "pipeline.h"

class FilterFactory {
public:
    using TFilterProducer = AbstractFilter* (*)(const FilterDescriptor&);
    using FilterMakerDict = std::map<std::string, TFilterProducer>;  // добавляет гибкости

public:
    void InitPipeline(const std::vector<FilterDescriptor>& filter_descriptors, Pipeline& pipeline) const;

    void AddProducer(const char* filter_typename, TFilterProducer filter_producer);

    // оборачиваем в этот интерфейс, чтобы там была вся логика поиска (чтобы можно было поменять мапу на что-то другое)
    TFilterProducer GetProducer(const char* filter_typename) const;

private:
    FilterMakerDict producers_;
};

#endif