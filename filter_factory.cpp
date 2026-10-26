#include "filter_factory.h"
#include "pipeline.h"

#include <exception>

FilterFactory::TFilterProducer FilterFactory::GetProducer(const char* filter_typename) const {
    FilterMakerDict::const_iterator it = producers_.find(filter_typename);
    if (it == producers_.end()) {
        return nullptr;
    }
    return it->second;
}

void FilterFactory::AddProducer(const char* filter_typename, TFilterProducer filter_producer) {
    if (GetProducer(filter_typename) != nullptr) {
        throw std::invalid_argument("дублирование продюсера с уже имеющимся именем фильтра");
    }
    producers_.insert({filter_typename, filter_producer});
}

void FilterFactory::InitPipeline(const std::vector<FilterDescriptor>& filter_descriptors, Pipeline& pl) const {
    for (const FilterDescriptor& fd : filter_descriptors) {
        FilterFactory::TFilterProducer producer = GetProducer(fd.name);
        if (!producer) {
            continue;  // неизвестный фильтр
        }
        AbstractFilter* filter = producer(fd);
        if (!filter) {
            throw std::invalid_argument("нет продюсера для известного фильтра");
        }
        pl.AddFilter(filter);
    }
}