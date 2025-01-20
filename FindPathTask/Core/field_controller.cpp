#include "field_controller.h"
#include "../UI/blocks/field/cell.h"


FieldController::FieldController(QObject *parent)
    : QObject{parent},
    m_height(0),
    m_width(0),
    m_isSearchStarted(false),
    m_isSearchEnded(false),
    m_pathfinder(new PathFinder(this))
{
    connect(this, &FieldController::dontFindPath, this, &FieldController::clean );
}

void FieldController::setStartCell(Cell* startCell)
{
    m_startCell = startCell;
}

Cell *FieldController::getStartCell()
{
    return m_startCell;
}

bool FieldController::isSearchStarted()
{
    return m_isSearchStarted;
}

bool FieldController::isSearchEnded()
{
    return m_isSearchEnded;
}

void FieldController::findPath()
{
    //resetGrid();
    m_pathfinder->find(m_grid, m_startCell, m_endCell);
}

void FieldController::clean()
{
    if (m_startCell) {
        m_startCell->setCellText("");
        m_startCell = nullptr;
    }

    if (m_endCell) {
        m_endCell->setCellText("");
        m_endCell = nullptr;
    }
    m_isSearchStarted = false;
    m_isSearchEnded = false;
    cleanGrid();
}

void FieldController::cleanGrid()
{
    for (const auto& row : m_grid) {
        for (Cell* cell : row) {
            cell->setCellText("");
            cell->visited = false;
            cell->parent = nullptr;
        }
    }
    emit cleanField();
}

void FieldController::setWidth(const uint16_t& newWidth)
{
    if(m_width == newWidth) {
        return;
    }
    m_width = newWidth;
}

uint16_t FieldController::getWidth() const
{
    return m_width;
}

void FieldController::setHeight(const uint16_t& newHeight)
{
    if(m_height == newHeight) {
        return;
    }
    m_height = newHeight;
}

uint16_t FieldController::getHeight() const
{
    return m_height;
}

void FieldController::initiateGrid(uint16_t height, uint16_t width)
{
    m_grid.clear();
    m_grid.resize(height, QVector<Cell*>(width));
}

void FieldController::addItemInGrid(int row, int col, Cell *cell)
{
    if (row < 0 || row >= m_grid.size() || col < 0 || col >= m_grid[0].size()
        || cell == nullptr) {
        return;
    }
    m_grid[row][col] = cell;
}

void FieldController::setWall(int row, int col, bool isWall)
{
    m_grid[row][col]->isWall = isWall;
}


void FieldController::onCellClicked(Cell* clickedCell)
{
    // Если ячейка является стеной, игнорируем клик
    if (clickedCell->isWall) {
        return;
    }

    // Если поиск не начат, устанавливаем начальную ячейку
    if (!isSearchStarted()) {
        cleanGrid();
        m_startCell = clickedCell;
        clickedCell->setCellText("A");
        m_isSearchStarted = true;
        return;
    }

    clickedCell->setCellText("B");
    m_isSearchEnded = true;
    m_isSearchStarted = false;

    // // Если поиск завершен, очищаем состояние
    // if (isSearchEnded()) {
    //     clean();
    // }

    // // Если поиск не начат, устанавливаем начальную ячейку
    // if (!isSearchStarted()) {
    //     m_startCell = clickedCell;
    //     clickedCell->setCellText("A");
    //     m_isSearchStarted = true;
    //     return;
    // }

    // // Если поиск начат, но не завершен, и конечная ячейка еще не установлена
    // if (!isSearchEnded() && m_endCell == nullptr) {
    //     m_endCell = clickedCell;
    //     findPath();
    //     clickedCell->setCellText("B");
    //     m_isSearchEnded = true;
    //     m_isSearchStarted = false;
    //     return;
    // }

    // // Если пользователь кликает на уже установленную начальную ячейку
    // if (clickedCell == m_startCell) {
    //     m_startCell->setCellText("");
    //     m_startCell = nullptr;
    //     return;
    // }

    // // Если пользователь кликает на уже установленную конечную ячейку
    // if (clickedCell == m_endCell) {
    //     m_endCell->setCellText("");
    //     m_endCell = nullptr;
    //     return;
    // }
}

void FieldController::onMouseMove(Cell *selectedCell)
{
    // Если ячейка является стеной, игнорируем клик
    if (selectedCell->isWall) {
        return;
    }

    if (!isSearchStarted()) {
        return;
    }
    // Если наведенная ячейка уже является начальной, ничего не делаем
    if (selectedCell == m_startCell) {
        return;
    }

    // if (selectedCell == m_endCell) {
    //     return;
    // }

    // Если поиск начат
    if (isSearchStarted()) {
        cleanGrid();
        m_endCell = selectedCell;
        findPath();
        //selectedCell->setCellText("B");
        //m_startCell = selectedCell;
        //m_isSearchEnded = true;
        //m_isSearchStarted = false;
        return;
    }

    // // Если поиск начат, но не завершен, и конечная ячейка еще не установлена
    // if (!isSearchEnded() && m_endCell == nullptr) {
    //     m_endCell = selectedCell;
    //     findPath();
    //     selectedCell->setCellText("B");
    //     m_isSearchEnded = true;
    //     m_isSearchStarted = false;

    //     m_startCell = selectedCell;
    //     return;
    // }

    // // Если поиск уже завершен, обновляем конечную ячейку и пересчитываем путь
    // if (isSearchEnded()) {
    //     m_endCell = selectedCell;
    //     findPath();
    //     selectedCell->setCellText("B");
    // }

    //m_endCell = selectedCell;
    //selectedCell->setCellText("A");

   // findPath();


}
