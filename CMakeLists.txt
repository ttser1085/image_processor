add_executable(
        image_processor
        image_processor.cpp
        BMPHandler.cpp BMPHandler.h Image.cpp Image.h AbstractFilter.cpp AbstractFilter.h ChannelWiseFilter.cpp ChannelWiseFilter.h ConvFilter.cpp ConvFilter.h ThresholdFilter.cpp ThresholdFilter.h CompositeFilter.cpp CompositeFilter.h CropFilter.cpp CropFilter.h GrayscaleFilter.cpp GrayscaleFilter.h NegativeFilter.cpp NegativeFilter.h SharpeningFilter.cpp SharpeningFilter.h EdgeFilter.cpp EdgeFilter.h GaussianBlurFilter.cpp GaussianBlurFilter.h Parser.cpp Parser.h CrystallizeFilter.cpp CrystallizeFilter.h)

add_catch(test_crop BMPHandler.cpp Image.cpp CropFilter.cpp tests/test_crop.cpp ChannelWiseFilter.cpp AbstractFilter.cpp)
add_catch(test_neg BMPHandler.cpp Image.cpp NegativeFilter.cpp tests/test_neg.cpp ChannelWiseFilter.cpp AbstractFilter.cpp)
add_catch(test_sharp BMPHandler.cpp Image.cpp SharpeningFilter.cpp tests/test_sharp.cpp ConvFilter.cpp ChannelWiseFilter.cpp AbstractFilter.cpp)
add_catch(test_gs BMPHandler.cpp Image.cpp GrayscaleFilter.cpp tests/test_gs.cpp AbstractFilter.cpp)
add_catch(test_edge BMPHandler.cpp Image.cpp EdgeFilter.cpp tests/test_edge.cpp CompositeFilter.cpp ConvFilter.cpp ChannelWiseFilter.cpp ThresholdFilter.cpp GrayscaleFilter.cpp AbstractFilter.cpp)
add_catch(test_blur BMPHandler.cpp Image.cpp GaussianBlurFilter.cpp tests/test_blur.cpp CompositeFilter.cpp ConvFilter.cpp ChannelWiseFilter.cpp AbstractFilter.cpp)
add_catch(test_parser Image.cpp Parser.cpp tests/test_parser.cpp AbstractFilter.cpp EdgeFilter.cpp GaussianBlurFilter.cpp CompositeFilter.cpp
        CrystallizeFilter.cpp SharpeningFilter.cpp ConvFilter.cpp NegativeFilter.cpp CropFilter.cpp
        ChannelWiseFilter.cpp GrayscaleFilter.cpp ThresholdFilter.cpp AbstractFilter.cpp)
add_catch(test_bmp BMPHandler.cpp Image.cpp tests/test_bmp.cpp)
