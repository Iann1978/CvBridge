cmake_minimum_required (VERSION 2.6)

set(OPENCV_LIB opencv_aruco344d.lib
	opencv_bgsegm344d.lib
	opencv_bioinspired344d.lib
	opencv_calib3d344d.lib
	opencv_ccalib344d.lib
	opencv_core344d.lib
	opencv_datasets344d.lib
	opencv_dnn_objdetect344d.lib
	opencv_dnn344d.lib
	opencv_dpm344d.lib
	opencv_face344d.lib
	opencv_features2d344d.lib
	opencv_flann344d.lib
	opencv_fuzzy344d.lib
	opencv_hfs344d.lib
	opencv_highgui344d.lib
	opencv_img_hash344d.lib
	opencv_imgcodecs344d.lib
	opencv_imgproc344d.lib
	opencv_line_descriptor344d.lib
	opencv_ml344d.lib
	opencv_objdetect344d.lib
	opencv_optflow344d.lib
	opencv_phase_unwrapping344d.lib
	opencv_photo344d.lib
	opencv_plot344d.lib
	opencv_reg344d.lib
	opencv_rgbd344d.lib
	opencv_saliency344d.lib
	opencv_shape344d.lib
	opencv_stereo344d.lib
	opencv_stitching344d.lib
	opencv_structured_light344d.lib
	opencv_superres344d.lib
	opencv_surface_matching344d.lib
	opencv_text344d.lib
	opencv_tracking344d.lib
	opencv_ts344d.lib
	opencv_video344d.lib
	opencv_videoio344d.lib
	opencv_videostab344d.lib
	opencv_xfeatures2d344d.lib
	opencv_ximgproc344d.lib
	opencv_xobjdetect344d.lib
	opencv_xphoto344d.lib)
	
set (OPENCV_INCLUDE 
	E:/githome/opencv/opencv3_4/build
	E:/githome/opencv/opencv3_4/include
	E:/githome/opencv/opencv3_4/include/opencv
	E:/githome/opencv/opencv3_4/modules/core/include
	E:/githome/opencv/opencv3_4/modules/flann/include
	E:/githome/opencv/opencv3_4/modules/imgproc/include
	E:/githome/opencv/opencv3_4/modules/ml/include
	E:/githome/opencv/opencv_contrib_3_4/modules/phase_unwrapping/include
	E:/githome/opencv/opencv3_4/modules/photo/include
	E:/githome/opencv/opencv_contrib_3_4/modules/plot/include
	E:/githome/opencv/opencv_contrib_3_4/modules/reg/include
	E:/githome/opencv/opencv_contrib_3_4/modules/surface_matching/include
	E:/githome/opencv/opencv3_4/modules/video/include
	E:/githome/opencv/opencv_contrib_3_4/modules/xphoto/include
	E:/githome/opencv/opencv3_4/modules/dnn/include
	E:/githome/opencv/opencv_contrib_3_4/modules/fuzzy/include
	E:/githome/opencv/opencv_contrib_3_4/modules/hfs/include
	E:/githome/opencv/opencv_contrib_3_4/modules/img_hash/include
	E:/githome/opencv/opencv3_4/modules/imgcodecs/include
	E:/githome/opencv/opencv3_4/modules/shape/include
	E:/githome/opencv/opencv3_4/modules/videoio/include
	E:/githome/opencv/opencv3_4/modules/highgui/include
	E:/githome/opencv/opencv3_4/modules/superres/include
	E:/githome/opencv/opencv3_4/modules/ts/include
	E:/githome/opencv/opencv_contrib_3_4/modules/bioinspired/include
	E:/githome/opencv/opencv_contrib_3_4/modules/dnn_objdetect/include
	E:/githome/opencv/opencv3_4/modules/features2d/include
	E:/githome/opencv/opencv_contrib_3_4/modules/line_descriptor/include
	E:/githome/opencv/opencv_contrib_3_4/modules/saliency/include
	E:/githome/opencv/opencv_contrib_3_4/modules/text/include
	E:/githome/opencv/opencv3_4/modules/calib3d/include
	E:/githome/opencv/opencv_contrib_3_4/modules/ccalib/include
	E:/githome/opencv/opencv_contrib_3_4/modules/datasets/include
	E:/githome/opencv/opencv3_4/modules/objdetect/include
	E:/githome/opencv/opencv_contrib_3_4/modules/rgbd/include
	E:/githome/opencv/opencv_contrib_3_4/modules/stereo/include
	E:/githome/opencv/opencv_contrib_3_4/modules/structured_light/include
	E:/githome/opencv/opencv_contrib_3_4/modules/tracking/include
	E:/githome/opencv/opencv3_4/modules/videostab/include
	E:/githome/opencv/opencv_contrib_3_4/modules/xfeatures2d/include
	E:/githome/opencv/opencv_contrib_3_4/modules/ximgproc/include
	E:/githome/opencv/opencv_contrib_3_4/modules/xobjdetect/include
	E:/githome/opencv/opencv_contrib_3_4/modules/aruco/include
	E:/githome/opencv/opencv_contrib_3_4/modules/bgsegm/include
	E:/githome/opencv/opencv_contrib_3_4/modules/dpm/include
	E:/githome/opencv/opencv_contrib_3_4/modules/face/include
	E:/githome/opencv/opencv_contrib_3_4/modules/optflow/include
	E:/githome/opencv/opencv3_4/modules/stitching/include)
	
project (CVBridgePlugins)


add_subdirectory(Plugin)

add_subdirectory(AVMDemo)

add_subdirectory(Calibration)