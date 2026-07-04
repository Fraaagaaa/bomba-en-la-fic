const formatDate = (date) => {
    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, '0');
    const day = String(date.getDate()).padStart(2, '0');

    return `${year}-${month}-${day}`;
};

const addDays = (date, days) => {
    const next = new Date(date);

    next.setDate(next.getDate() + days);

    return next;
};

const DateSelector = ({ value, onChange, id, className }) => {
    const today = new Date();

    const options = [];
    for (let i = 0; i < 7; i++) {
        const date = addDays(today, i);
        const val = formatDate(date);
        const label = date.toLocaleDateString();
        options.push({ val, label });
    }

    return (
        <div className={className}>
            <select
                id={id}
                className="form-select"
                value={value}
                onChange={e => onChange(e.target.value)}
            >
                {options.map((opt) => (
                    <option key={opt.val} value={opt.val}>
                        {opt.label}
                    </option>
                ))}
            </select>
        </div>
    );
};

export default DateSelector;