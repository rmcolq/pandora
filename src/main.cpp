#include <iostream>
#include <cstring>
#include "CLI11.hpp"
#include "index_main.h"
#include "map_main.h"
#include "compare_main.h"
#include "walk_main.h"

class MyFormatter : public CLI::Formatter {
public:
    std::string make_option_opts(const CLI::Option* opt) const override
    {
        std::stringstream out;

        if (opt->get_type_size() != 0) {
            if (!opt->get_type_name().empty())
                out << " " << get_label(opt->get_type_name());
            else if (opt->get_expected_min() > 1)
                out << " x " << opt->get_expected();

            if (opt->get_required())
                out << " " << get_label("[required]");
        }
        if (!opt->get_envname().empty())
            out << " (" << get_label("Env") << ":" << opt->get_envname() << ")";
        if (!opt->get_needs().empty()) {
            out << " " << get_label("Needs") << ":";
            for (const CLI::Option* op : opt->get_needs())
                out << " " << op->get_name();
        }
        if (!opt->get_excludes().empty()) {
            out << " " << get_label("Excludes") << ":";
            for (const CLI::Option* op : opt->get_excludes())
                out << " " << op->get_name();
        }
        return out.str();
    }

    std::string make_option_desc(const CLI::Option* opt) const override
    {
        std::stringstream out;
        out << opt->get_description();
        if (!opt->get_default_str().empty()) {
            out << " [default: " << opt->get_default_str() << "]";
        }
        return out.str();
    }
};

int pandora_index(int argc, char* argv[]);

int pandora_walk(int argc, char* argv[]);

int pandora_map(int argc, char* argv[]);

int pandora_compare(int argc, char* argv[]);

int pandora_check_kmergraph(int argc, char* argv[]);

int pandora_get_vcf_ref(int argc, char* argv[]);

int pandora_random_path(int argc, char* argv[]);

int pandora_merge_index(int argc, char* argv[]);

static int usage()
{
    std::cerr
        << "         random_path   outputs a fasta of random paths through the PRGs\n"
        << "         get_vcf_ref   outputs a fasta suitable for use as the VCF "
           "reference using input sequences\n"
        << "         merge_index   allows multiple indexes to be merged (no "
           "compatibility check)\n"
        << std::endl;
    return 1;
}

int main(int argc, char* argv[])
{
    CLI::App app { "Pandora, Pan-genome inference and genotyping with long noisy or "
                   "short accurate reads." };
    app.formatter(std::make_shared<MyFormatter>());
    setup_index_subcommand(app);
    setup_map_subcommand(app);
    setup_compare_subcommand(app);
    setup_walk_subcommand(app);
    app.require_subcommand();

    CLI11_PARSE(app, argc, argv);

    return 0;

    //    int ret;
    //    if (argc < 2)
    //        return usage();
    //    if (strcmp(argv[1], "index") == 0)
    //        ret = pandora_index(argc - 1, argv + 1);
    //    else if (strcmp(argv[1], "walk") == 0)
    //        ret = pandora_walk(argc - 1, argv + 1);
    //    else if (strcmp(argv[1], "map") == 0)
    //        ret = pandora_map(argc - 1, argv + 1);
    //    else if (strcmp(argv[1], "compare") == 0)
    //        ret = pandora_compare(argc - 1, argv + 1);
    //    else if (strcmp(argv[1], "check_kmergraph") == 0)
    //        ret = pandora_check_kmergraph(argc - 1, argv + 1);
    //    else if (strcmp(argv[1], "get_vcf_ref") == 0)
    //        ret = pandora_get_vcf_ref(argc - 1, argv + 1);
    //    else if (strcmp(argv[1], "random_path") == 0)
    //        ret = pandora_random_path(argc - 1, argv + 1);
    //    else if (strcmp(argv[1], "merge_index") == 0)
    //        ret = pandora_merge_index(argc - 1, argv + 1);
    //    else {
    //        fprintf(stderr, "[main] unrecognized command '%s'\n", argv[1]);
    //        return 1;
    //    }
    //    return ret;
}
