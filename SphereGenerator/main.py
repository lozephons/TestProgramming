import numpy

sample_points = []
with open('sphere_sample_points.txt') as sample_points_reader:
    # load sample points     
    for sample_point_in_string in sample_points_reader.readlines():
        sample_point_in_string = sample_point_in_string.strip()
        sample_point = sample_point_in_string.split(' ')

        sample_point_v3 = [float(sample_point[0]), float(sample_point[1]), float(sample_point[2])]
        sample_points.append(sample_point_v3)

    # process sample points
    sample_points_num = len(sample_points)   

    num_loops = 80
    for loop_count in range(num_loops):
        # add new points
        new_sample_points = []
        for index in range(0, sample_points_num, 2):
            # when index is out of range
            if (index + 1 > sample_points_num):
                break

            # add new point
            new_sample_point = numpy.add(sample_points[index], sample_points[index + 1])
            new_sample_point = numpy.divide(new_sample_point, 2)
            new_sample_points.append(new_sample_point)

        sample_points.extend(new_sample_points)

    total_num_points = len(sample_points)

    sample_points_reader.close()        
    
# write the text
with open('sphere_sample_points1.txt', 'w+') as sample_points_writer:

    for sample_point in sample_points:
        sample_point_in_string = [str(sample_point[0]), str(sample_point[1]), str(sample_point[2])]
        combined_sample_point_in_string = ' '.join(sample_point_in_string)
        sample_points_writer.write(combined_sample_point_in_string + '\n')
    
    sample_points_writer.close()
    
