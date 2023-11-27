#pragma once
#include <list>
#include <string>
#include <vector>



struct PeerPursuit {
    std::vector<std::vector<double>> opse {
        {0, 0}, {0, 0}, {-13, -13}, 
{-22, -22}, {-26, -26}, {-30, -30}, {-38, -38}, 
{-131, -31}, {-114, -46}, {-114, -46}, {-113, -47}, 
{-103, -57}, {-104, -58}, {-113, -49}, {-153, -9}, 
{-156, -6}, {-152, -8}, {-79, -79}, {-81, -81}, 
{-81, -81}, {-80, -80}, {-87, -87}, {-95, -95}, 
{-95, -95}, {-96, -96}, {-98, -98}, {-101, -101}, 
{-104, -104}, {-104, -104}, {-104, -104}, {0, 0}
    };

    std::vector<std::string> autopt1 {
    "0, 0, 88.904", "0, -0.994, 87.472", "0, -1.994, 86.008", "0, -2.994, 84.519", 
		"0, -3.994, 83.003", "0, -4.994, 81.458", "0, -5.994, 79.884", "-0.117, -6.98, 78.29", 
		"-0.356, -7.951, 76.65", "-0.596, -8.922, 74.975", "-0.835, -9.892, 73.262", "-1.07, -10.864, 71.507", 
		"-1.263, -11.846, 69.709", "-1.455, -12.827, 67.862", "-1.648, -13.808, 65.964", "-1.887, -14.779, 64.011", 
		"-2.133, -15.748, 61.995", "-2.379, -16.718, 59.911", "-2.653, -17.679, 57.754", "-2.96, -18.63, 55.511", 
		"-3.267, -19.582, 53.174", "-3.58, -20.532, 50.73", "-3.962, -21.456, 48.161", "-4.345, -22.38, 45.448", 
		"-4.728, -23.304, 42.562", "-5.163, -24.203, 39.467", "-5.616, -25.095, 36.106", "-6.068, -25.987, 32.398", 
		"-6.553, -26.861, 28.21", "-7.068, -27.718, 23.277", "-7.583, -28.575, 16.965", "-8.098, -29.432, 5.816", 
		"-8.167, -29.546, 0", "-8.167, -29.546, 0", "-18.47, -46.688, 0", "endData"
    };

		std::vector<std::string> autopt1v2 {
    "-13.824, 61.356, 76.911", "-13.008, 60.778, 75.242", "-12.191, 60.201, 73.534", "-11.375, 59.623, 71.786", 
		"-10.615, 58.974, 69.996", "-9.867, 58.311, 68.158", "-9.118, 57.648, 66.268", "-8.406, 56.95, 64.328", 
		"-7.765, 56.182, 62.323", "-7.124, 55.414, 60.251", "-6.497, 54.637, 58.108", "-6.02, 53.758, 55.88", 
		"-5.544, 52.879, 53.559", "-5.067, 52, 51.132", "-4.742, 51.059, 48.596", "-4.461, 50.099, 45.908", 
		"-4.181, 49.139, 43.053", "-3.967, 48.166, 40.006", "-3.856, 47.172, 36.694", "-3.744, 46.178, 33.052", 
		"-3.696, 45.183, 29.039", "-3.757, 44.185, 25.027", "-3.817, 43.187, 21.014", "-3.878, 42.188, 21.014", 
		"-4.105, 41.215, 21.014", "-4.343, 40.244, 17.627", "-4.581, 39.273, 7.531", "-4.634, 39.056, 0", 
		"-4.634, 39.056, 0", "-9.394, 19.631, 0", "endData"
    };

    
    std::vector<std::string> autopt2 {
    "-4.096, -21.897, 100", "-4.281, -20.914, 100", "-4.466, -19.932, 100", "-4.652, -18.949, 100", 
		"-4.841, -17.967, 100", "-5.031, -16.985, 100", "-5.221, -16.003, 100", "-5.418, -15.023, 100", 
		"-5.626, -14.045, 100", "-5.835, -13.067, 100", "-6.043, -12.089, 100", "-6.285, -11.119, 100", 
		"-6.53, -10.149, 100", "-6.775, -9.18, 100", "-7.059, -8.221, 100", "-7.35, -7.264, 100", 
		"-7.64, -6.307, 99.254", "-7.96, -5.361, 97.968", "-8.34, -4.436, 96.663", "-8.72, -3.511, 95.34", 
		"-9.1, -2.586, 93.998", "-9.538, -1.687, 92.638", "-9.994, -0.798, 91.257", "-10.45, 0.092, 89.855", 
		"-10.932, 0.967, 88.431", "-11.456, 1.82, 86.983", "-11.979, 2.672, 85.51", "-12.515, 3.515, 84.013", 
		"-13.112, 4.318, 82.487", "-13.708, 5.121, 80.933", "-14.305, 5.923, 79.348", "-14.982, 6.658, 77.732", 
		"-15.664, 7.389, 76.081", "-16.346, 8.121, 74.393", "-17.039, 8.841, 72.666", "-17.768, 9.526, 70.897", 
		"-18.497, 10.211, 69.082", "-19.225, 10.896, 67.219", "-19.984, 11.547, 100", "-20.743, 12.199, 99.137", 
		"-21.501, 12.85, 97.847", "-22.265, 13.496, 96.541", "-23.033, 14.136, 95.216", "-23.801, 14.776, 93.873", 
		"-24.57, 15.416, 92.51", "-25.344, 16.049, 91.127", "-26.118, 16.683, 89.722", "-26.891, 17.316, 88.295", 
		"-27.667, 17.947, 86.845", "-28.444, 18.577, 85.37", "-29.22, 19.207, 83.869", "-29.996, 19.838, 82.341", 
		"-30.772, 20.469, 80.784", "-31.547, 21.101, 79.196", "-32.323, 21.732, 77.576", "-33.096, 22.366, 75.921", 
		"-33.87, 23, 74.23", "-34.644, 23.633, 72.499", "-35.413, 24.272, 70.725", "-36.181, 24.912, 68.906", 
		"-36.95, 25.552, 67.038", "-37.716, 26.194, 65.116", "-38.482, 26.838, 63.135", "-39.247, 27.481, 61.091", 
		"-40.011, 28.127, 58.975", "-40.773, 28.774, 56.781", "-41.536, 29.421, 54.498", "-42.297, 30.07, 52.116", 
		"-43.053, 30.723, 49.619", "-43.81, 31.377, 46.99", "-44.567, 32.03, 44.205", "-45.327, 32.68, 50.845", 
		"-46.087, 33.33, 48.283", "-46.847, 33.98, 45.576", "-47.608, 34.629, 100", "-48.369, 35.278, 100", 
		"-49.13, 35.927, 100", "-49.901, 36.563, 100", "-50.675, 37.197, 100", "-51.448, 37.831, 100", 
		"-52.228, 38.457, 100", "-53.017, 39.071, 100", "-53.806, 39.686, 100", "-54.592, 40.304, 100", 
		"-55.369, 40.933, 100", "-56.146, 41.562, 100", "-56.923, 42.192, 100", "-57.696, 42.827, 100", 
		"-58.468, 43.462, 100", "-59.24, 44.098, 100", "-60.021, 44.722, 100", "-60.807, 45.34, 100", 
		"-61.593, 45.959, 100", "-62.396, 46.554, 100", "-63.224, 47.114, 100", "-64.052, 47.675, 100", 
		"-64.908, 48.186, 100", "-65.819, 48.599, 98.941", "-66.729, 49.012, 97.649", "-67.654, 49.387, 96.343", 
		"-68.615, 49.663, 95.015", "-69.576, 49.94, 93.669", "-70.541, 50.198, 92.305", "-71.528, 50.363, 90.918", 
		"-72.514, 50.528, 89.511", "-73.5, 50.693, 88.08", "-74.492, 50.812, 86.628", "-75.489, 50.885, 85.149", 
		"-76.487, 50.957, 83.645", "-77.484, 51.03, 82.112", "-78.484, 51.031, 80.551", "-79.484, 51.027, 78.959", 
		"-80.484, 51.023, 77.334", "-81.481, 50.955, 75.675", "-82.477, 50.865, 73.977", "-83.473, 50.775, 72.24", 
		"-84.465, 50.653, 70.462", "-85.451, 50.489, 68.636", "-86.438, 50.325, 66.76", "-87.416, 50.127, 64.832", 
		"-88.382, 49.864, 62.842", "-89.347, 49.602, 60.788", "-90.312, 49.34, 58.661", "-91.239, 48.97, 56.458", 
		"-92.159, 48.577, 54.162", "-93.078, 48.185, 51.764", "-93.979, 47.756, 49.256", "-94.822, 47.217, 46.606", 
		"-95.664, 46.679, 43.796", "-96.507, 46.14, 40.794", "-97.301, 45.533, 37.553", "-98.087, 44.916, 34.004", 
		"-98.874, 44.298, 30.038", "-99.63, 43.645, 25.464", "-100.368, 42.97, 19.86", "-101.107, 42.296, 11.85", 
		"-101.515, 41.923, 0", "-101.515, 41.923, 0", "-116.283, 28.435, 0", "endData"
    };

    std::vector<std::string> autopt3 {
    "-118.566, -31.025, 91.955", "-118.486, -30.028, 90.564", "-118.407, -29.031, 89.15", "-118.327, -28.035, 87.714", 
		"-118.251, -27.037, 86.254", "-118.175, -26.04, 84.769", "-118.1, -25.043, 83.257", "-118.033, -24.045, 81.718", 
		"-117.972, -23.047, 80.148", "-117.91, -22.049, 78.548", "-117.863, -21.05, 76.914", "-117.841, -20.051, 75.245", 
		"-117.819, -19.051, 73.538", "-117.807, -18.051, 71.791", "-117.848, -17.052, 69.999", "-117.889, -16.053, 68.161", 
		"-117.93, -15.054, 66.271", "-118.001, -14.057, 64.327", "-118.108, -13.063, 62.322", "-118.216, -12.068, 60.25", 
		"-118.345, -11.077, 58.158", "-118.529, -10.095, 56.065", "-118.713, -9.112, 53.973", "-118.898, -8.129, 51.881", 
		"-119.16, -7.165, 49.789", "-119.452, -6.209, 47.697", "-119.744, -5.252, 45.605", "-120.036, -4.296, 43.513", 
		"-120.094, -3.302, 41.421", "-120.116, -2.302, 39.328", "-120.137, -1.302, 37.236", "-120.159, -0.303, 35.144", 
		"-120.181, 0.697, 33.052", "-120.203, 1.697, 33.052", "-120.224, 2.697, 33.052", "-120.246, 3.697, 33.052", 
		"-120.268, 4.696, 33.052", "-120.29, 5.696, 33.052", "-120.311, 6.696, 33.052", "-120.333, 7.696, 33.052", 
		"-120.355, 8.695, 33.052", "-120.377, 9.695, 33.052", "-120.399, 10.695, 33.052", "-120.42, 11.695, 33.052", 
		"-120.442, 12.694, 33.052", "-120.464, 13.694, 33.052", "-120.486, 14.694, 33.052", "-120.507, 15.694, 33.052", 
		"-120.529, 16.693, 33.052", "-120.551, 17.693, 33.052", "-120.573, 18.693, 33.052", "-120.594, 19.693, 33.052", 
		"-120.616, 20.692, 33.052", "-120.638, 21.692, 33.052", "-120.66, 22.692, 33.052", "-120.682, 23.692, 33.052", 
		"-120.703, 24.692, 33.052", "-120.725, 25.691, 33.052", "-120.747, 26.691, 33.052", "-120.769, 27.691, 33.052", 
		"-120.79, 28.691, 33.052", "-120.812, 29.69, 33.052", "-120.834, 30.69, 33.052", "-120.856, 31.69, 33.052", 
		"-120.877, 32.69, 33.052", "-120.899, 33.689, 33.052", "-120.921, 34.689, 33.052", "-120.943, 35.689, 33.052", 
		"-120.964, 36.689, 33.052", "-120.986, 37.688, 33.052", "-121.008, 38.688, 33.052", "-121.03, 39.688, 33.052", 
		"-121.052, 40.688, 33.052", "-121.073, 41.688, 33.052", "-121.095, 42.687, 33.052", "-121.117, 43.687, 33.052", 
		"-121.139, 44.687, 33.052", "-121.16, 45.687, 33.052", "-121.182, 46.686, 33.052", "-121.204, 47.686, 33.052", 
		"-121.226, 48.686, 33.052", "-121.247, 49.686, 33.052", "-121.269, 50.685, 33.052", "-121.291, 51.685, 33.052", 
		"-121.313, 52.685, 33.052", "-121.334, 53.685, 33.052", "-121.356, 54.684, 33.052", "-121.378, 55.684, 33.052", 
		"-121.4, 56.684, 33.052", "-121.422, 57.684, 33.052", "-121.443, 58.683, 33.052", "-121.465, 59.683, 33.052", 
		"-121.495, 59.135, 33.052", "-121.527, 58.136, 33.052", "-121.559, 57.136, 33.052", "-121.591, 56.137, 33.052", 
		"-121.623, 55.137, 33.052", "-121.655, 54.138, 33.052", "-121.687, 53.138, 33.052", "-121.719, 52.139, 33.052", 
		"-121.751, 51.139, 33.052", "-121.783, 50.14, 33.052", "-121.815, 49.14, 33.052", "-121.847, 48.141, 33.052", 
		"-121.879, 47.141, 33.052", "-121.911, 46.142, 33.052", "-121.943, 45.142, 33.052", "-121.975, 44.143, 33.052", 
		"-122.007, 43.143, 33.052", "-122.039, 42.144, 33.052", "-122.071, 41.144, 33.052", "-122.103, 40.145, 33.052", 
		"-122.135, 39.145, 33.052", "-122.167, 38.146, 33.052", "-122.199, 37.146, 33.052", "-122.231, 36.147, 33.052", 
		"-122.263, 35.148, 33.052", "-122.295, 34.148, 33.052", "-122.327, 33.149, 33.052", "-122.359, 32.149, 33.052", 
		"-122.392, 31.15, 33.052", "-122.424, 30.15, 33.052", "-122.456, 29.151, 33.052", "-122.488, 28.151, 33.052", 
		"-122.52, 27.152, 33.052", "-122.552, 26.152, 33.052", "-122.584, 25.153, 33.052", "-122.616, 24.153, 33.052", 
		"-122.648, 23.154, 33.052", "-122.68, 22.154, 33.052", "-122.712, 21.155, 33.052", "-122.744, 20.155, 33.052", 
		"-122.776, 19.156, 33.052", "-122.808, 18.156, 33.052", "-122.84, 17.157, 33.052", "-122.872, 16.157, 33.052", 
		"-122.904, 15.158, 33.052", "-122.936, 14.158, 33.052", "-122.968, 13.159, 33.052", "-123, 12.159, 33.052", 
		"-123.032, 11.16, 33.052", "-123.064, 10.16, 33.052", "-123.096, 9.161, 33.052", "-123.128, 8.161, 33.052", 
		"-123.16, 7.162, 33.052", "-123.192, 6.162, 33.052", "-123.224, 5.163, 33.052", "-123.256, 4.163, 33.052", 
		"-123.288, 3.164, 33.052", "-123.32, 2.164, 33.052", "-123.956, 2.883, 33.052", "-124.606, 3.643, 33.052", 
		"-125.257, 4.402, 31.4", "-125.953, 5.117, 27.064", "-126.689, 5.795, 21.873", "-127.425, 6.472, 14.981", 
		"-128.075, 7.07, 0", "-128.075, 7.07, 0", "-142.792, 20.613, 0", "endData"
    };


    std::vector<std::string> autopt4 {
    "-125.487, 2.02, 27.033", "-124.633, 1.5, 27.005", "-123.778, 0.981, 26.978", "-122.924, 0.461, 26.95", 
		"-122.771, 1.298, 26.922", "-122.701, 2.296, 26.895", "-122.63, 3.293, 26.867", "-122.56, 4.291, 26.839", 
		"-122.49, 5.289, 26.812", "-122.42, 6.286, 26.784", "-122.349, 7.284, 26.756", "-122.279, 8.281, 26.729", 
		"-122.209, 9.279, 26.701", "-122.138, 10.276, 26.673", "-122.068, 11.274, 26.646", "-121.998, 12.271, 26.618", 
		"-121.927, 13.269, 26.59", "-121.857, 14.266, 26.563", "-121.787, 15.264, 26.535", "-121.717, 16.261, 26.507", 
		"-121.646, 17.259, 26.48", "-121.576, 18.256, 26.452", "-121.506, 19.254, 26.424", "-121.435, 20.251, 26.397", 
		"-121.365, 21.249, 26.369", "-121.295, 22.246, 26.341", "-121.224, 23.244, 26.314", "-121.154, 24.241, 26.286", 
		"-121.084, 25.239, 26.258", "-121.013, 26.237, 26.231", "-120.943, 27.234, 26.203", "-120.873, 28.232, 26.175", 
		"-120.803, 29.229, 26.148", "-120.732, 30.227, 26.12", "-120.662, 31.224, 26.092", "-120.592, 32.222, 26.064", 
		"-120.521, 33.219, 26.037", "-120.451, 34.217, 26.009", "-120.381, 35.214, 25.981", "-120.31, 36.212, 25.954", 
		"-120.24, 37.209, 25.926", "-120.17, 38.207, 25.898", "-120.1, 39.204, 25.871", "-120.029, 40.202, 25.843", 
		"-119.959, 41.199, 25.815", "-119.889, 42.197, 25.788", "-119.818, 43.194, 25.76", "-119.748, 44.192, 25.732", 
		"-119.678, 45.19, 25.705", "-119.607, 46.187, 25.677", "-119.537, 47.185, 25.649", "-119.467, 48.182, 25.622", 
		"-119.396, 49.18, 25.594", "-119.327, 49.899, 25.566", "-119.263, 48.901, 25.539", "-119.198, 47.903, 25.511", 
		"-119.134, 46.905, 25.483", "-119.069, 45.907, 25.456", "-119.005, 44.909, 25.428", "-118.94, 43.911, 25.4", 
		"-118.876, 42.913, 25.373", "-118.812, 41.915, 25.345", "-118.747, 40.917, 25.317", "-118.683, 39.92, 25.29", 
		"-118.618, 38.922, 25.262", "-118.554, 37.924, 25.234", "-118.489, 36.926, 25.207", "-118.425, 35.928, 25.179", 
		"-118.36, 34.93, 25.151", "-118.296, 33.932, 25.124", "-118.232, 32.934, 25.096", "-118.167, 31.936, 25.068", 
		"-118.103, 30.938, 25.041", "-118.038, 29.94, 25.013", "-117.974, 28.942, 24.985", "-117.909, 27.945, 24.958", 
		"-117.845, 26.947, 24.93", "-117.781, 25.949, 24.902", "-117.716, 24.951, 24.875", "-117.652, 23.953, 24.847", 
		"-117.587, 22.955, 24.819", "-117.523, 21.957, 24.792", "-117.458, 20.959, 24.764", "-117.394, 19.961, 24.736", 
		"-117.329, 18.963, 24.708", "-117.265, 17.965, 24.681", "-117.201, 16.967, 24.653", "-117.136, 15.969, 24.625", 
		"-117.072, 14.972, 24.625", "-117.007, 13.974, 24.625", "-116.943, 12.976, 24.625", "-116.878, 11.978, 24.625", 
		"-116.814, 10.98, 24.625", "-116.75, 9.982, 24.625", "-116.685, 8.984, 24.625", "-116.621, 7.986, 24.625", 
		"-116.556, 6.988, 24.625", "-116.492, 5.99, 24.625", "-116.427, 4.992, 24.625", "-116.363, 3.994, 24.625", 
		"-116.298, 2.996, 24.625", "-116.234, 1.999, 24.625", "-116.17, 1.001, 24.625", "-116.105, 0.003, 24.625", 
		"-116.041, -0.995, 24.625", "-115.976, -1.993, 24.625", "-115.034, -2.32, 24.625", "-114.088, -2.645, 24.625", 
		"-113.142, -2.969, 24.625", "-112.21, -3.329, 24.625", "-111.293, -3.729, 24.625", "-110.376, -4.128, 24.625", 
		"-109.472, -4.552, 24.625", "-108.611, -5.06, 24.625", "-107.75, -5.569, 24.625", "-106.893, -6.083, 24.625", 
		"-106.108, -6.703, 23.459", "-105.323, -7.322, 17.215", "-104.538, -7.942, 6.508", "-104.407, -8.045, 0", 
		"-104.407, -8.045, 0", "-88.707, -20.435, 0", "endData"
    };
    
    
    std::vector<std::string> skills {
    "6.468, 18.804, 59.427", "5.76, 18.098, 57.25", "5.051, 17.392, 54.987", "4.343, 16.686, 52.627", 
		"3.66, 15.956, 100", "2.977, 15.225, 100", "2.295, 14.495, 100", "1.649, 13.731, 100", 
		"1.004, 12.967, 100", "0.359, 12.202, 100", "-0.232, 11.398, 100", "-0.793, 10.569, 100", 
		"-1.353, 9.741, 100", "-1.835, 8.868, 100", "-2.261, 7.964, 100", "-2.687, 7.059, 100", 
		"-3.032, 6.124, 100", "-3.3, 5.161, 100", "-3.569, 4.197, 100", "-3.801, 3.226, 100", 
		"-3.949, 2.237, 100", "-4.097, 1.248, 100", "-4.24, 0.259, 100", "-4.298, -0.739, 100", 
		"-4.355, -1.738, 100", "-4.413, -2.736, 100", "-4.433, -3.736, 100", "-4.446, -4.736, 100", 
		"-4.46, -5.736, 100", "-4.466, -6.736, 100", "-4.467, -7.736, 100", "-4.467, -8.736, 100", 
		"-4.459, -9.736, 100", "-4.441, -10.735, 100", "-4.423, -11.735, 100", "-4.405, -12.735, 100", 
		"-4.388, -13.735, 98.985", "-4.371, -14.735, 97.693", "-4.355, -15.735, 96.385", "-4.346, -16.735, 95.058", 
		"-4.337, -17.735, 93.712", "-4.328, -18.735, 92.347", "-4.33, -19.735, 90.961", "-4.333, -20.735, 89.554", 
		"-4.337, -21.734, 88.125", "-4.344, -22.734, 86.672", "-4.352, -23.734, 85.194", "-4.36, -24.734, 83.69", 
		"-4.369, -25.734, 82.158", "-4.377, -26.734, 80.598", "-4.386, -27.734, 79.006", "-4.392, -28.734, 77.382", 
		"-4.397, -29.734, 75.723", "-4.402, -30.734, 74.027", "-4.401, -31.734, 72.291", "-4.397, -32.734, 70.512", 
		"-4.392, -33.734, 68.688", "-4.388, -34.734, 66.813", "-4.384, -35.734, 64.884", "-4.38, -36.734, 62.897", 
		"-4.378, -37.734, 60.844", "-4.378, -38.734, 58.72", "-4.379, -39.734, 56.515", "-4.383, -40.734, 54.222", 
		"-4.393, -41.734, 51.827", "-4.404, -42.734, 49.315", "-4.418, -43.734, 46.669", "-4.439, -44.734, 43.863", 
		"-4.459, -45.734, 40.866", "-4.482, -46.733, 37.63", "-4.508, -47.733, 34.088", "-4.535, -48.733, 30.133", 
		"-4.564, -49.732, 25.573", "-4.6, -50.731, 20", "-4.636, -51.731, 20", "-4.671, -52.73, 20", 
		"-4.7, -53.73, 20", "-4.728, -54.729, 20", "-4.755, -55.729, 20", "-4.755, -56.729, 20", 
		"-4.755, -57.729, 20", "-4.755, -58.729, 20", "-4.661, -59.724, 20", "-4.565, -60.72, 20", 
		"-4.468, -61.715, 20", "-4.257, -62.692, 20", "-4.038, -63.668, 20", "-3.819, -64.644, 20", 
		"-3.447, -65.568, 20", "-3.031, -66.477, 20", "-2.615, -67.387, 20", "-1.969, -68.132, 20", 
		"-1.244, -68.821, 20", "-0.519, -69.509, 20", "0.224, -70.176, 20", "1.015, -70.788, 20", 
		"1.806, -71.4, 20", "2.745, -71.669, 20", "3.733, -71.825, 20", "4.721, -71.981, 20", 
		"5.711, -71.941, 20", "6.703, -71.815, 20", "7.695, -71.689, 20", "8.662, -71.454, 20", 
		"9.605, -71.123, 20", "10.549, -70.793, 20", "11.467, -70.403, 20", "12.354, -69.94, 20", 
		"13.24, -69.476, 20", "14.106, -68.979, 20", "14.944, -68.433, 20", "15.781, -67.887, 20", 
		"16.597, -67.31, 20", "17.375, -66.682, 20", "18.154, -66.055, 20", "18.889, -65.383, 20", 
		"19.528, -64.614, 20", "20.168, -63.846, 20", "20.771, -63.053, 20", "21.223, -62.161, 20", 
		"21.675, -61.269, 20", "22.127, -60.377, 20", "22.421, -59.421, 20", "22.713, -58.465, 17.274", 
		"23.005, -57.508, 6.664", "23.056, -57.341, 0", "23.056, -57.341, 0", "28.897, -38.213, 0", 
		"endData"
            };

		std::vector<std::string> skillspt2 {
    "0, -72.627, 47.498", "0.308, -73.578, 47.498", "0.617, -74.53, 47.498", "0.925, -75.481, 47.498", 
		"1.359, -76.38, 47.498", "1.813, -77.271, 47.498", "2.268, -78.162, 47.498", "2.723, -79.052, 47.498", 
		"3.18, -79.941, 47.498", "3.637, -80.831, 47.498", "4.097, -81.719, 47.498", "4.568, -82.601, 47.498", 
		"5.039, -83.483, 47.498", "5.52, -84.36, 47.498", "6.037, -85.215, 47.498", "6.554, -86.071, 47.498", 
		"7.074, -86.925, 47.498", "7.68, -87.721, 47.498", "8.286, -88.516, 47.498", "8.892, -89.312, 47.498", 
		"9.577, -90.036, 47.498", "10.307, -90.719, 47.498", "11.038, -91.402, 47.498", "11.845, -91.981, 47.498", 
		"12.716, -92.472, 47.498", "13.587, -92.963, 47.498", "14.497, -93.364, 47.498", "15.451, -93.662, 47.498", 
		"16.406, -93.961, 47.498", "17.367, -94.229, 47.498", "18.357, -94.369, 47.498", "19.347, -94.508, 47.498", 
		"20.338, -94.648, 47.498", "21.334, -94.722, 47.498", "22.333, -94.777, 47.498", "23.331, -94.831, 47.498", 
		"23.492, -94.869, 47.498", "22.492, -94.884, 44.997", "21.492, -94.899, 42.08", "21.002, -94.908, 40.575", 
		"22.002, -94.902, 37.314", "23.002, -94.896, 33.739", "24.002, -94.884, 29.738", "25, -94.823, 25.107", 
		"25.998, -94.762, 19.4", "26.996, -94.7, 11.062", "27.477, -94.671, 0", "27.477, -94.671, 0", 
		"47.44, -93.448, 0", "endData"
            };
    

    std::vector<std::string> skillsPt2 {
        "endData"
    };

    std::vector<std::string> placehold4Curve {
		"36.98, 12.445, 100", "36, 12.244, 100", "35.021, 12.043, 100", "34.041, 11.841, 100", 
		"33.058, 11.661, 100", "32.069, 11.515, 100", "31.08, 11.369, 100", "30.088, 11.242, 100", 
		"29.09, 11.183, 100", "28.092, 11.124, 100", "27.094, 11.065, 100", "26.096, 11.071, 100", 
		"25.099, 11.147, 100", "24.102, 11.223, 100", "23.105, 11.299, 100", "22.11, 11.395, 100", 
		"21.13, 11.593, 100", "20.15, 11.791, 100", "19.17, 11.992, 99.311", "18.207, 12.26, 98.024", 
		"17.244, 12.528, 96.72", "16.28, 12.797, 95.398", "15.326, 13.094, 94.057", "14.374, 13.401, 92.697", 
		"13.423, 13.709, 91.317", "12.475, 14.029, 89.915", "11.532, 14.36, 88.492", "10.588, 14.691, 87.045", 
		"9.647, 15.029, 85.573", "8.711, 15.382, 84.076", "7.776, 15.735, 82.552", "6.84, 16.088, 80.999", 
		"5.91, 16.455, 79.415", "4.98, 16.822, 77.8", "4.05, 17.19, 76.15", "3.123, 17.564, 74.463", 
		"2.196, 17.94, 72.738", "1.269, 18.317, 70.97", "0.345, 18.697, 69.158", "-0.579, 19.079, 67.296", 
		"-1.503, 19.462, 65.382", "-2.427, 19.845, 63.41", "-3.35, 20.229, 61.374", "-4.273, 20.614, 59.269", 
		"-5.198, 20.995, 57.086", "-6.127, 21.366, 54.816", "-7.055, 21.736, 52.448", "-7.984, 22.107, 49.968", 
		"-8.923, 22.451, 47.36", "-9.875, 22.754, 44.598", "-10.828, 23.057, 41.653", "-11.781, 23.361, 38.483", 
		"-12.736, 23.653, 35.031", "-13.73, 23.766, 31.196", "-14.724, 23.879, 26.818", "-15.717, 23.992, 21.568", 
		"-16.711, 24.105, 14.533", "-17.537, 24.199, 0", "-17.537, 24.199, 0", "-37.409, 26.458, 0", 
		"endData"
    };

};
