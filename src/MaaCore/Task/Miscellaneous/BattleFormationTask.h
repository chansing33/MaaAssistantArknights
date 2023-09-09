#pragma once
#include "Common/AsstBattleDef.h"
#include "Task/AbstractTask.h"

namespace asst
{
    class BattleFormationTask : public AbstractTask
    {
    public:
        using AbstractTask::AbstractTask;
        virtual ~BattleFormationTask() override = default;

        enum class Filter
        {
            None,
            Trust,
            Cost,
        };
        struct AdditionalFormation
        {
            Filter filter = Filter::None;
            bool double_click_filter = true;
            battle::RoleCounts role_counts;
        };
        void append_additional_formation(AdditionalFormation formation);

        void set_support_unit_name(std::string name);
        void set_add_trust(bool add_trust);

        enum class DataResource
        {
            Copilot,
            SSSCopilot,
        };
        void set_data_resource(DataResource resource);

    protected:
        using OperGroup = std::vector<battle::OperUsage>;

        virtual bool _run() override;
        // 追加附加干员（按部署费用等小分类）
        bool add_additional();
        // 补充刷信赖的干员，从最小的开始
        bool add_trust_operators();

        bool enter_selection_page();
        bool select_opers_in_cur_page(std::vector<OperGroup>& groups);
        void swipe_page();
        void swipe_to_the_left(int times = 2);
        bool confirm_selection();
        bool click_role_table(battle::Role role);
        bool parse_formation();
        bool select_random_support_unit();

        std::vector<TextRect> analyzer_opers();

        std::string m_stage_name;
        std::unordered_map<battle::Role, std::vector<OperGroup>> m_formation;
        // 编队中干员个数
        int m_operators_in_formation = 0;
        // 是否需要追加信赖干员
        bool m_add_trust = false;
        std::string m_support_unit_name;
        DataResource m_data_resource = DataResource::Copilot;
        std::vector<AdditionalFormation> m_additional;
        std::string m_last_oper_name;
    };
}
