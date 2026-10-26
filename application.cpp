#include "application.h"

#include "producers.h"

const char* const IMAGE_PROCESSOR_HELP =
    "Usage: ./program input_file output_file -filter_name_1 arg1 arg2 ... -filter_name2 arg1 ...\n"
    "Filters:\n"
    "Saturation: names={sat, saturation}, args={double multiplier}\n"
    "Crop: names={crop}, args={int new_width, int new_height}\n"
    "Grayscale: names={gs, grayscale}, no args\n"
    "Negative: names={neg, negative}, no args\n"
    "Sharpening: names={sharp, sharpening}, no args\n"
    "Edge: names={edge}, args={double border}\n"
    "Blur: names={blur}, args={double sigma}";

const char* const SEE_HELP = "Run program without arguments to see help.";

// выполняем статическое конфигурирование нашего приложения
void Application::Init() {
    // crop
    factory_.AddProducer("crop", MakeCropFilter);
    // saturation
    factory_.AddProducer("saturation", MakeSaturationFilter);
    factory_.AddProducer("sat", MakeSaturationFilter);
    // grayscale
    factory_.AddProducer("gs", MakeGrayscaleFilter);
    factory_.AddProducer("grayscale", MakeGrayscaleFilter);
    // negative
    factory_.AddProducer("neg", MakeNegativeFilter);
    factory_.AddProducer("negative", MakeNegativeFilter);
    // sharpening
    factory_.AddProducer("sharp", MakeSharpeningFilter);
    factory_.AddProducer("sharpening", MakeSharpeningFilter);
    // edge
    factory_.AddProducer("edge", MakeEdgeFilter);
    // blur
    factory_.AddProducer("blur", MakeBlurFilter);
}

Application::Result Application::Run(int argc, char* argv[]) {
    Parser::Result result = parser_.Parse(argc, argv);
    if (result == Parser::Result::NoArguments) {
        Help();
        return Result::Failed;
    }
    if (result == Parser::Result::FewArguments) {
        FewArgs();
        return Result::Failed;
    }
    if (result == Parser::Result::InvalidArguments) {
        InvalidArgs();
        return Result::Failed;
    }
    Pipeline pipeline;
    factory_.InitPipeline(parser_.GetFilters(), pipeline);
    Bmp pic;
    bool read_status = pic.ReadBmp(parser_.GetInputName());
    if (!read_status) {
        Print("File read failed");
        return Result::ReadFailed;
    }
    bool pipeline_status = pipeline.Apply(pic);
    if (!pipeline_status) {
        Print("Pipeline failed");
        return Result::PipelineFailed;
    }
    bool write_status = pic.WriteBmp(parser_.GetOutputName());
    if (!write_status) {
        Print("Write failed");
        return Result::WriteFailed;
    }
    return Result::Success;
}