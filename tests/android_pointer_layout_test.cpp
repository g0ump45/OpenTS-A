#include "../code/android_pointer_layout.h"
#include <array>
#include <cassert>
int main() {
    using namespace android_pointer;
    for (auto size : {Size{640,480},Size{1920,1080},Size{2208,1840},Size{2560,1600},Size{3840,2160}}) {
        for (bool top : {false,true}) {
            auto view = presentation_view(size.width,size.height,true,top);
            assert(view.width==640 && view.height==480);
            assert(view.x==(size.width-640)/2);
            assert(view.y==(top?0:(size.height-480)/2));
            int const sw=std::min(size.width,640*size.height/480);
            int const sh=std::min(size.height,480*size.width/640);
            for (auto point : {Size{110,160},Size{320,400},Size{530,440}}) {
                int px=(size.width-sw)/2+point.width*sw/640;
                int py=(size.height-sh)/2+point.height*sh/480;
                auto mapped=map_window(view,size.width,size.height,px,py);
                assert(std::abs(mapped.width-(view.x+point.width))<=1);
                assert(std::abs(mapped.height-(view.y+point.height))<=1);
            }
        }
        auto world=presentation_view(size.width,size.height,false,false);
        assert(world.x==0 && world.y==0 && world.width==size.width && world.height==size.height);
    }
    for (int left : {0, 168}) {
        assert(edges(left + 10, 100, left, 16, 640, 464) == 0);
        assert(edges(left, 100, left, 16, 640, 464) == 1);
        assert(edges(left + 639, 100, left, 16, 640, 464) == 2);
        assert(edges(left + 320, 16, left, 16, 640, 464) == 4);
        assert(edges(left + 320, 479, left, 16, 640, 464) == 8);
        assert(edges(left, 16, left, 16, 640, 464) == 5);
        assert(edges(left - 1, 100, left, 16, 640, 464) == 0);
        assert(edges(left + 640, 100, left, 16, 640, 464) == 0);
        assert(edges(left + 639, 480, left, 16, 640, 464) == 0);
        assert(edges(left + 320, 15, left, 16, 640, 464) == 0);
    }
    for (int mode = 0; mode <= 3; ++mode) {
        auto a = resolution(mode, 1920, 1080);
        assert(a.width >= 640 && a.height >= 480);
        assert(a.width * 1080 - a.height * 1920 <= 1080);
        assert(a.width * 1080 - a.height * 1920 >= -1080);
        auto fold = resolution(mode, 2208, 1840);
        assert(fold.width >= 640);
        assert(std::abs(fold.width * 1840 - fold.height * 2208) <= 2208);
    }
    for (auto size : {Size{640,480},Size{1280,720},Size{1280,800},Size{1920,1080},Size{1920,1200},
        Size{2048,1536},Size{2400,1080},Size{2560,1600},Size{2208,1840},Size{3840,2160}})
        assert(valid_custom_resolution(size.width,size.height));
    for (auto size : {Size{0,0},Size{-1,720},Size{639,480},Size{1280,479},Size{720,1280},
        Size{3841,2160},Size{3840,2400},Size{9999,9999}})
        assert(!valid_custom_resolution(size.width,size.height));
    assert(resolution(3, 1920, 1080).height == 720);
    assert(resolution(2, 1920, 1080).height == 600);
    std::array<std::uint16_t, 24> pixels;
    pixels.fill(0x1234);
    unsigned char const indices[] = {0, 1, 2, 0};
    unsigned short const palette[] = {0xffff, 0, 0x07e0};
    draw_cursor(pixels.data() + 4, 4, 4, 4, indices, 2, 2, palette, 1, 1, 2, 2);
    assert(pixels[4 + 1 * 4 + 1] == 0x1234);
    assert(pixels[4 + 1 * 4 + 2] == 0);
    assert(pixels[4 + 2 * 4 + 1] == 0x07e0);
    for (int i=0;i<4;++i) { assert(pixels[i]==0x1234); assert(pixels[20+i]==0x1234); }
    draw_cursor(pixels.data() + 4, 4, 4, 4, indices, 2, 2, palette, -2, -2, 4, 4);
    draw_cursor(pixels.data() + 4, 4, 4, 4, indices, 2, 2, palette, 3, 3, 4, 4);
    for (int i=0;i<4;++i) { assert(pixels[i]==0x1234); assert(pixels[20+i]==0x1234); }
}
