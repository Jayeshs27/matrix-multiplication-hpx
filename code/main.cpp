#include <hpx/algorithm.hpp>
#include <hpx/init.hpp>

#include <iostream>
#include <random>
#include <vector>


void print_matrix(std::vector<int> mat, int row, int col){
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            std::cout << mat[i * col + j] << " ";
        }
        std::cout << std::endl;
    }
}

int hpx_main()
{
    int l, m, n;
    std::cin >> l >> m >> n;
    const int row_mat1 = l;
    const int col_mat1 = m;
    const int row_mat2 = m;
    const int col_mat2 = n;

    unsigned int seed = std::random_device{}();
    seed = 13;

    std::mt19937 gen(seed);  

    std::uniform_int_distribution<int> dist(0, 10);
    auto generator = std::bind(dist, gen);

    std::vector<int> mat1(l * m);
    std::vector<int> mat2(m * n);
    std::vector<int> mat_res(l * n);

    hpx::ranges::generate(mat1, generator);
    hpx::ranges::generate(mat2, generator);
    hpx::ranges::generate(mat_res, generator);

    hpx::experimental::for_loop(hpx::execution::par, 0, row_mat1, [&](auto i) {
        hpx::experimental::for_loop(0, col_mat2, [&](auto j){
            mat_res[i * col_mat2 + j] = 0;
            hpx::experimental::for_loop(0, row_mat2, [&](auto k){
                mat_res[i * col_mat2 + j] += mat1[i * col_mat1 + k] * mat2[k * col_mat2 + j];
            });
        });
    });

    print_matrix(mat1, row_mat1, col_mat1);
    print_matrix(mat2, row_mat2, col_mat2);
    print_matrix(mat_res, row_mat1, col_mat2);
    return hpx::local::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::local::init(hpx_main, argc, argv);
}